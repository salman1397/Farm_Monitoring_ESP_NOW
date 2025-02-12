#include <WiFi.h>
#include <esp_now.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define MOISTURE_PIN 33

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

const int rs = 14, en = 12, d4 = 25, d5 = 5, d6 = 18, d7 = 19, a = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define a struct to hold the sensor data
typedef struct {
  float temperature;
  float humidity;
  int moisture;
} SensorData;

SensorData data;

// Receiver MAC Address
uint8_t receiverAddress[] = {0x10, 0x06, 0x1C, 0x81, 0x11, 0xEC}; //receiver's MAC address

// Callback function to check sending status
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  pinMode(a, OUTPUT);
  
  // Initialize the DHT sensor and LCD
  dht.begin();
  lcd.begin(16, 2);  // Start LCD
  digitalWrite(a, HIGH);

  // Initialize WiFi in station mode
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(onDataSent);

  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Read temperature and humidity from DHT11
  data.temperature = dht.readTemperature();
  data.humidity = dht.readHumidity();
  
  // Check if DHT read was successful
  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read moisture sensor value
  data.moisture = map(analogRead(MOISTURE_PIN), 0, 4095, 100, 0);

  // Display data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(data.temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(data.humidity);
  lcd.print("  M: ");
  lcd.print(data.moisture);

  // Send data to receiver ESP32
  esp_now_send(receiverAddress, (uint8_t *) &data, sizeof(data));

  delay(2000);  // Update every 2 seconds
}