# 🛠️ IoT-Based Water Level and Quality Monitoring System  
*A real-time IoT system for monitoring water level, pH, and turbidity using ESP8266*

---

## 📌 Overview  
This project implements a low-cost, real-time **IoT-based water monitoring system** capable of measuring:

- **Water Level** using HC-SR04 Ultrasonic Sensor  
- **pH Level** using ATmega8 pH Sensor  
- **Turbidity** using TS-300B Sensor  

The ESP8266 (ESP-12E) reads data from all sensors, processes the values, displays them on an **OLED display**, and uploads the information to the **Blynk IoT Cloud** for remote monitoring.  
This system is ideal for water quality assessment in reservoirs, tanks, agriculture, and environmental monitoring.

---

## 🎯 Features  
- ✔ Real-time water level measurement  
- ✔ pH monitoring for acidity/alkalinity  
- ✔ Turbidity measurement for water clarity  
- ✔ ESP-12E microcontroller with Wi-Fi  
- ✔ OLED display for local viewing  
- ✔ Blynk Cloud Dashboard for remote access  
- ✔ Low-cost and easily scalable IoT solution  

---

## 🧩 System Architecture  
The system consists of the following modules:

### **Sensors**
- **HC-SR04 Ultrasonic Sensor** – Water level  
- **ATmega8-based pH Sensor** – Acidity/alkalinity  
- **TS-300B Turbidity Sensor** – Water clarity  

### **Controller**
- **ESP-12E (ESP8266)**  
  - Processes sensor data  
  - Sends values to Blynk  
  - Displays data on OLED  

### **User Interface**
- OLED Display (local monitoring)  
- Blynk Web & Mobile Dashboard (remote monitoring)

---

## 🔌 Wiring Summary  
| Component           | ESP12E Pin |
|--------------------|------------|
| Ultrasonic Trigger | D6         |
| Ultrasonic Echo    | D7         |
| pH Sensor Output   | A0         |
| Turbidity Sensor   | D4         |
| OLED SDA           | D2         |
| OLED SCL           | D1         |
| Power & Ground     | 3.3V / GND |

---

## 📊 Data Flow  
1. Sensors measure **water level, pH, and turbidity**  
2. ESP8266 acquires and calibrates data  
3. Values are displayed on **OLED screen**  
4. Data is uploaded to **Blynk Cloud**  
5. User monitors readings remotely through mobile/web dashboard  


---

## 🧪 Results  
The system successfully measured:  
- **Water level** (ultrasonic)  
- **pH level** (ATmega8 sensor)  
- **Turbidity** (TS-300B sensor)  

Data was updated in real time on both:  
- 📍 Local OLED Display  
- 🌐 Blynk Cloud Interface (charts, gauges, history)

---

## 📝 How to Run  

### **1️⃣ Install Requirements**
- Arduino IDE  
- ESP8266 Board Add-on  
- Blynk Library  
- OLED SSD1306 Library  

### **2️⃣ Upload Code to ESP12E**
Connect ESP12E → Select COM Port → Upload code.

### **3️⃣ Configure Blynk**
- Add device in Blynk Console  
- Insert **Template ID** and **Device Token** in code  

### **4️⃣ Power Up System**
Readings appear on OLED + Blynk Dashboard.

---

## 🔮 Future Enhancements  
- Integration of temperature & dissolved oxygen sensors  
- AI/ML-based contamination prediction  
- SMS/WhatsApp alert alerts  
- Solar-powered IoT deployment  
- Automatic water treatment controls  

---


