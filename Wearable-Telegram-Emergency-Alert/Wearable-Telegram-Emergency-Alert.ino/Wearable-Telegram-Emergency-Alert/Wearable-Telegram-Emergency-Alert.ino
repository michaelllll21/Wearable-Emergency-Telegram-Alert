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


void connectWiFi() {
  Serial.println("\n Attempting to connect to Wi-Fi networks...");

  const char* ssids[] = {wifi1_ssid, wifi2_ssid, wifi3_ssid};
  const char* passwords[] = {wifi1_password, wifi2_password, wifi3_password};
  const char* names[] = {"PLDT", "TP-Link", "Hotspot"};

  for (int i = 0; i < 3; i++) {
    Serial.print(" Trying ");
    Serial.print(names[i]);
    Serial.println("...");

    WiFi.begin(ssids[i], passwords[i]);
    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
      delay(500);
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("\n Connected to ");
      Serial.println(names[i]);
      Serial.print(" IP Address: ");
      Serial.println(WiFi.localIP());
      return;
    }

    Serial.println("\n Failed to connect. Moving to next network...");
  }

  Serial.println("\n Unable to connect to any network!");
}

void setup() {
  Serial.begin(115200);
  delay(2000); 
  pinMode(BUTTON, INPUT_PULLUP);

  connectWiFi();

  client.setInsecure(); 
  client.setTimeout(5000); 
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    Serial.println(" Button Pressed!");
    sendTelegramMessage("🚨 URGENT NOTICE: Michael requires immediate assistance. This alert was sent automatically by his ESP8266 emergency device.");
    delay(2000);
  }
}


void sendTelegramMessage(String message) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(" Wi-Fi lost! Reconnecting...");
    connectWiFi();
  }

  Serial.println(" Connecting to Telegram...");
  if (!client.connect(telegramHost, 443)) {
    Serial.println(" Connection to Telegram failed!");
    return;
  }

  String url = "/bot" + telegramToken + "/sendMessage?chat_id=" + chatID + "&text=" + message;
  Serial.println(" Sending alert to Telegram...");

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + telegramHost + "\r\n" +
               "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.connected() && millis() - timeout < 5000) {
    while (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
      timeout = millis();
    }
  }

  Serial.println(" Telegram message attempt finished!");
  client.stop();
}
