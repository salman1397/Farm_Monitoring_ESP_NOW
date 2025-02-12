#include <WiFi.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  delay(100);
  //10:06:1C:81:11:EC  10:06:1C:81:11:EC

}

void loop() {
  // put your main code here, to run repeatedly:

}
