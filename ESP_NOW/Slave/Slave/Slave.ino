#include <esp_now.h>
#include <WiFi.h>
typedef struct struct_message {
  float temperature;
  float humidity;
  int soilMoisture;
} struct_message;

struct_message sensorData;

void InitESPNow() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-NOW initialized successfully");
  } else {
    Serial.println("ESP-NOW initialization failed");
    ESP.restart();
  }
}

void OnDataRecv(const esp_now_recv_info *recvInfo, const uint8_t *data, int data_len) {
  memcpy(&sensorData, data, sizeof(sensorData));

  Serial.println("Data Received:");
  Serial.print("Temperature: ");
  Serial.println(sensorData.temperature);
  Serial.print("Humidity: ");
  Serial.println(sensorData.humidity);
  Serial.print("Soil Moisture: ");
  Serial.println(sensorData.soilMoisture);
}

void setup() {
  Serial.begin(115200);
  InitESPNow();
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing to do in the loop
}
