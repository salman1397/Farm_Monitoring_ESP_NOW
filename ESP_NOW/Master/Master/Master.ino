#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>
#include "esp_system.h"

#define DHTPIN 4       // Pin where the DHT11 is connected
#define DHTTYPE DHT11  // Define DHT sensor type
#define MOISTURE_PIN 33 // Pin for soil moisture sensor
DHT dht(DHTPIN, DHTTYPE);
#define SLEEP_TIME 10 * 1000000UL  // 30 seconds in microseconds

typedef struct struct_message {
  float temperature;
  float humidity;
  int soilMoisture;
  float systemp;
} struct_message;

struct_message sensorData;

// Slave MAC address  10:06:1C:81:11:EC    10:06:1C:81:11:EC
uint8_t slaveMAC[] = {0x10, 0x06, 0x1C, 0x81, 0x11, 0xEC};

bool isSlaveConnected = false;

void InitESPNow() {
  WiFi.mode(WIFI_STA);  // Set ESP32 to Station mode
  WiFi.disconnect();    // Ensure the ESP32 is disconnected from any network
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-NOW initialized successfully");
  } else {
    Serial.println("ESP-NOW initialization failed");
    ESP.restart();  // Restart if initialization failed
    delay(100);
  }
}

// Callback function to check the status of sent messages
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  dht.begin();

  // Initialize ESP-NOW
  InitESPNow();
  
  // Register send callback
  esp_now_register_send_cb(OnDataSent);

  // Add the peer (Slave)
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, slaveMAC, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) == ESP_OK) {
    Serial.println("Slave added successfully");
    isSlaveConnected = true;
    digitalWrite(2, HIGH);
  } else {
    Serial.println("Failed to add Slave");
    isSlaveConnected = false;
    digitalWrite(2, LOW);
  }
}

void loop() {
  if (isSlaveConnected) {
    // Read data from sensors
    sensorData.temperature = dht.readTemperature();
    sensorData.humidity = dht.readHumidity();
    sensorData.soilMoisture = (100-analogRead(MOISTURE_PIN)/40.95);  
    sensorData.systemp= temperatureRead();
    //(4095 to 0)    4095/40.95(100-0)   100-100=0    100-90=10
    digitalWrite(2, HIGH);

    // Check if any reads failed
    if (isnan(sensorData.temperature) || isnan(sensorData.humidity)) {
      Serial.println("Failed to read from DHT sensor");
    } else {
      // Print data to Serial for debugging
      Serial.println("Sending Data:");
      Serial.print("Temperature: ");
      Serial.println(sensorData.temperature);
      Serial.print("Humidity: ");
      Serial.println(sensorData.humidity);
      Serial.print("Soil Moisture: ");
      Serial.println(sensorData.soilMoisture);
      Serial.print("SystemTemp: ");
      Serial.println(sensorData.systemp);


      // Send data via ESP-NOW
      esp_now_send(slaveMAC, (uint8_t *)&sensorData, sizeof(sensorData));
    }
  } else {
    digitalWrite(2, LOW);
  }delay(250);
  esp_sleep_enable_timer_wakeup(SLEEP_TIME);
  esp_deep_sleep_start();

}
