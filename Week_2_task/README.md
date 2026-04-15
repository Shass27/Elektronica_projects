# Week 2 Task: ESP32 Touch to MQTT

## Problem Summary
Build an ESP32 firmware that reads capacitive touch input, calibrates a threshold from serial values, and treats a threshold crossing as a button press. On each touch edge, turn GPIO2 LED on and publish DETECTED to an MQTT topic over TCP port 1883. Implement FreeRTOS with two tasks: one for touch sensing/queueing and one for MQTT publishing after queue events.

## Project Structure
```text
Week_2_task/
├── Final_Code/
│   └── Final_Code.ino
└── Testing_codes/
    ├── RTOS_test/
    │   └── RTOS_test.ino
    ├── Touch_Calibration/
    │   └── Touch_Calibration.ino
    ├── WiFi_connectivity_test/
    │   └── WiFi_connectivity_test.ino
    └── WiFi_MQTT_connection/
        └── WiFi_MQTT_connection.ino
```

## Setup
1. Install Arduino IDE 2.x.
2. Install ESP32 board support:
   - Arduino IDE -> Preferences -> Additional Boards Manager URLs:
     `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Tools -> Board -> Boards Manager -> install `esp32` by Espressif Systems.
3. Install library:
   - Sketch -> Include Library -> Manage Libraries -> install `PubSubClient` by Nick O'Leary.
4. Connect the ESP32 board and select the correct board and serial port from Tools.
5. Use a 2.4 GHz Wi-Fi network (mobile hotspot is fine).

## Configure
1. Open `Final_Code/Final_Code.ino`.
2. Update Wi-Fi credentials:
   - `ssid`
   - `password`
3. Set your topic name in the publish path.
4. Calibrate touch threshold:
   - Upload `Testing_codes/Touch_Calibration/Touch_Calibration.ino`
   - Read touch values on Serial Monitor
   - Choose an experimental threshold and set `threshold` in `Final_Code.ino`.

## Build and Run
1. Upload `Final_Code/Final_Code.ino` to ESP32.
2. Open Serial Monitor at `115200` baud.
3. Confirm Wi-Fi and MQTT connection logs.
4. Subscribe to your topic using HiveMQ Web Client or MQTT Explorer.
5. Touch the configured touch pin:
   - LED on GPIO2 turns ON while touched and OFF otherwise.
   - `DETECTED` is published once per touch event (edge-triggered).