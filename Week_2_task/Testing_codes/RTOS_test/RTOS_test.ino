#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

int threshold = 1350;

void readTouch(void* touchParam) {
    while(1) {
        Serial.println("task 1 running");
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2, LOW);
        delay(500);
    }
}

void mqttPublish(void* pubParam) {
    while(1){
    Serial.println("task 2 running");
    delay(1000);
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    xTaskCreate(readTouch, "Read Touch", 4096, NULL, 1, NULL);
    xTaskCreate(mqttPublish, "MQTT Publish", 4096, NULL, 1, NULL);
}

void loop() {
    
}