#include <Arduino.h>
#include <WiFi.h>

const char* ssid = ""; // Enter your WiFi SSID here
const char* password = ""; // Enter your WiFi password here

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    int attempts = 0;
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        attempts++;
        delay(1000);
        Serial.print(".");
        if(attempts > 20) { // timeout
            Serial.println("\nFailed to connect to WiFi");
            return;
        }
    }
    Serial.println("Connected to WiFi");
}

void loop() {
}