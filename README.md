# Wearable Emergency Telegram Alert System  
A lightweight wearable IoT device designed to send an emergency alert message through Telegram with just **one button press**.

This project uses:  
- **NodeMCU ESP8266**  
- **Push Button**  
- **TP4056 charging module**  
- **3.7V Li-ion / LiPo battery**  
- **(Optional) Boost Converter 3.7V → 5V**  
- **Telegram Bot API**

---

##  Project Overview
The Wearable Emergency Telegram Alert System allows a person to send an emergency message instantly by pressing a single button.  
The ESP8266 automatically connects to one of the **three configured networks** (two WiFi networks + one mobile hotspot) to ensure reliability.

Once connected, the device sends a **formal emergency message** to a chosen Telegram account using a Telegram Bot.

This is designed for:
- People living alone  
- Seniors  
- People with disabilities  
- Outdoor workers  
- Anyone who needs a fast emergency alert device  

---

##  Features
-  Sends emergency alert to Telegram with **one button press**  
-  Automatically connects to **3 different networks**  
-  Uses secure HTTPS connection  
-  Works on **battery power**  
-  Rechargeable using TP4056  
-  Can be miniaturized and made wearable  

---

##  Hardware Requirements
| Component | Description |
|----------|-------------|
| ESP8266 NodeMCU | Main microcontroller with WiFi |
| TP4056 Charger | For charging the 3.7V battery |
| Li-ion / LiPo Battery | 3.7V battery for portable power |
| Boost Converter (optional) | If powering ESP via VIN |
| Push Button | Emergency trigger |
| JST Connectors | For safe wiring |
| Enclosure | For wearable version |

---

##  Wiring Diagram (Text Description)

**Battery → TP4056**
- Battery RED → B+  
- Battery BLACK → B-

**TP4056 Output → ESP**
- OUT+ → VIN or 5V of ESP  
- OUT- → GND of ESP  

**Button → ESP**
- One side → D1  
- Other side → GND  

---

##  Arduino Code
> Private credentials removed for safety.  
> Replace the empty fields with your own WiFi and Telegram Bot info.

```cpp
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define BUTTON D1

const char* wifi1_ssid = ;
const char* wifi1_password = ;

const char* wifi2_ssid = ;
const char* wifi2_password = ;

const char* wifi3_ssid = ;
const char* wifi3_password = ;

const char* telegramHost = ;
String telegramToken = ;
String chatID = ;

WiFiClientSecure client;
