#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

int threshold = 1350;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

const char* ssid = ""; // Enter your WiFi SSID here
const char* password = ""; // Enter your WiFi password here

void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);

    WiFi.begin(ssid, password);

    int attempts = 0;
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        attempts++;
        delay(1000);
        Serial.print(".");
        if(attempts > 10) { // timeout
            Serial.println("\nFailed to connect to WiFi");
            return;
        }
    }
    Serial.println("Connected to WiFi");

    client.setServer("broker.hivemq.com", 1883);
    attempts = 0;
    Serial.print("Connecting to MQTT Broker");
    while (!client.connected()) {
        client.connect("ShasClient");
        attempts++;
        if (attempts > 10) { // timeout
            Serial.println("\nFailed to connect to MQTT Broker");
            return;
        }
        Serial.print(".");
        delay(1000);
    }
    Serial.println("Connected to MQTT Broker");
}

void loop() {
    client.loop();
    if(client.connected()) {
        client.publish("elektronica/ME25BTECH11051/week2", "Hello from Shas");
        Serial.println("Message published to MQTT Broker");
        delay(1000);
    }
}