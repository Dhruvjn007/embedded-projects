// Arduino UNO R4 WiFi - TCP Server
// Listens for Pico's message and replies
// Run this first, then check Serial Monitor for the IP address
// Enter that IP in the Pico script

#include <WiFiS3.h>

// === CONFIGURE THESE ===
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";
// =======================

#define PORT 8080

WiFiServer server(PORT);

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("Arduino IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Copy this IP into the Pico script!");

  server.begin();
  Serial.println("Server started. Waiting for Pico...");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Pico connected!");

    String incoming = "";
    unsigned long startTime = millis();

    // Read incoming message (wait up to 2 seconds)
    while (millis() - startTime < 2000) {
      while (client.available()) {
        char c = client.read();
        incoming += c;
      }
      if (incoming.length() > 0) break;
      delay(10);
    }

    if (incoming.length() > 0) {
      Serial.print("Pico says: ");
      Serial.println(incoming);

      // Send reply
      String reply = "Hello I am Arduino UNO R4";
      client.print(reply);
      Serial.print("Arduino says: ");
      Serial.println(reply);
    }

    client.stop();
    Serial.println("Pico disconnected.");
    Serial.println("Waiting for next connection...\n");
  }
}
