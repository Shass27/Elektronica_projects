#include <Arduino.h>

#define TPIN 4

int threshold = 1350;

void setup() {
  Serial.begin(115200);
    pinMode(TPIN, INPUT);
    pinMode(2, OUTPUT);
}

void loop() {
    int touchVal = touchRead(TPIN);
    // Serial.println(touchVal);
    if (touchVal < threshold) {
        Serial.println("Touched");
        digitalWrite(2, HIGH);
    } else {
        Serial.println("Not Touched");
        digitalWrite(2, LOW);
    }
    delay(100);
}