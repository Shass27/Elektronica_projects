#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define TPIN 4
int threshold = 1350;
bool touchState = false;

#define LED 2

WiFiClient wifiClient;
PubSubClient client(wifiClient);

QueueHandle_t touchQueue = nullptr;

const char* ssid = ""; // Enter your WiFi SSID here
const char* password = ""; // Enter your WiFi password here

bool touchCheck() {
    int touchValue = touchRead(TPIN);
    return touchValue < threshold;
}

void readTouch(void* touchParam) {
    while(1) {
        bool currentState = touchCheck();
        if(currentState != touchState) {
            touchState = currentState;
            if(touchState) {
                xQueueSend(touchQueue, &touchState, portMAX_DELAY);
                digitalWrite(LED, HIGH);
            } else {
                digitalWrite(LED, LOW);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void mqttPublish(void* pubParam) {
    while(1){
        bool state;
        if(xQueueReceive(touchQueue, &state, portMAX_DELAY)) {
            if(client.connected() && state) {
                client.publish("elektronica/ME25BTECH11051/week2", "DETECTED");
            }
            else {
                Serial.println("MQTT Broker not connected");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    WiFi.begin(ssid, password);

    touchQueue = xQueueCreate(5, sizeof(bool));

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

    xTaskCreate(readTouch, "Read Touch", 4096, NULL, 1, NULL);
    xTaskCreate(mqttPublish, "Publish MQTT", 4096, NULL, 1, NULL);
}

void loop() {
    client.loop();
}