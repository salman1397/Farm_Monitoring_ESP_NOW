# 🌾 Farm Monitoring System using ESP32 & ESP-NOW
![Embedded Systems](https://readme-typing-svg.herokuapp.com?color=F7B42C&lines=Farm+Monitoring+System;ESP+NOW;Low+Power+Secure+Communication;With+Out+WiFi)

![Farm Monitoring Banner](assets/farm_monitoring_banner.gif)

## 🌟 Overview
The **Farm Monitoring System** is a smart agricultural solution using **ESP32** and **ESP-NOW Protocol** for real-time farm data collection and monitoring. The system enables **remote monitoring** of crucial environmental parameters such as:
- 🌡 **Temperature**
- 💧 **Humidity**
- 🌱 **Soil Moisture**
- ⚡ **Battery Level**

The system provides **low-power, long-range** communication without requiring **WiFi or the Internet**, making it ideal for large-scale farms and remote locations.

---

## 🚀 Features
✅ **Wireless data transmission using ESP-NOW**  
✅ **Real-time temperature & humidity monitoring**  
✅ **Soil moisture detection for irrigation management**  
✅ **Long-range communication without WiFi**  
✅ **Low power consumption for extended battery life**  
✅ **Graphical data representation on a dashboard**  

---

## 🛠️ Components Used
| Component | Description |
|-----------|------------|
| ![ESP32](assets/esp32.png) | ESP32 WiFi & BLE Module |
| ![DHT11](assets/dht11.png) | Temperature & Humidity Sensor |
| ![Soil Sensor](assets/soil_sensor.png) | Soil Moisture Sensor |
| ![Battery](assets/battery.png) | Rechargeable Battery Module |
| ![Solar Panel](assets/solar_panel.png) | Solar Panel for Powering the System |

---

## 📡 Working Principle
1️⃣ **ESP32 Sensor Nodes** collect environmental data (Temperature, Humidity, Soil Moisture, Battery Level).  
2️⃣ **ESP-NOW Protocol** transmits data wirelessly to the **ESP32 Gateway**.  
3️⃣ **ESP32 Gateway** processes and uploads the data to a cloud server or a local dashboard.  
4️⃣ Farmers access real-time farm data via a **web or mobile dashboard**.  
5️⃣ **Automated alerts** can be sent for irrigation needs based on soil moisture levels.  

---

## 📱 Data Visualization
The system provides real-time farm insights via:
- 📊 **Graphical dashboard (Web/App)**
- 🔔 **Automated alerts & notifications**
- 📡 **Remote access & monitoring**

![Farm Monitoring Dashboard](assets/farm_dashboard.png)

---

## 🔧 Installation & Setup
### 1️⃣ Hardware Setup
- Connect the **ESP32 Sensor Nodes** to the respective sensors.
- Power the system using **rechargeable batteries** and **solar panels**.
- Place nodes at various locations in the farm for optimal coverage.

### 2️⃣ Firmware & Code Upload
- Install **Arduino IDE** and **ESP32 Board Manager**.
- Upload the ESP-NOW firmware to both the **Sensor Nodes** and **Gateway**.
- Configure the gateway to send data to a local or cloud-based dashboard.

### 3️⃣ Data Visualization
- Use a **web or mobile dashboard** to monitor farm conditions.
- Set up alerts for **low soil moisture, extreme temperatures, and power issues**.

---

## 📸 System Demonstration
![Farm Monitoring Demo](assets/farm_demo.gif)

---

## ⚙️ Future Enhancements
- 🌐 **Integration with IoT Cloud Platforms**
- 🔋 **Optimized Low-Power Sleep Mode for Longer Battery Life**
- 💦 **Automated Irrigation System Integration**
- 📡 **LoRa-based Long-Distance Communication**

---

## 🏗️ Project Contributors
🔹 **[Your Name]** - Developer & Hardware Engineer  
🔹 **[Your GitHub](https://github.com/yourgithub)** - Repository Maintainer  

---

## 📜 License
This project is **open-source** and released under the **MIT License**.

---

## ⭐ Show Some Love!
If you liked this project, don't forget to **🌟 Star** the repo and **fork** it for future improvements!

[![GitHub Stars](https://img.shields.io/github/stars/yourgithub/farm-monitoring.svg?style=social)](https://github.com/yourgithub/farm-monitoring)

