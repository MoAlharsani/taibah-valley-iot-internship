# Building an IoT Interface with MIT App Inventor and MQTT

## Introduction
This document outlines a project where an interactive interface is created using MIT App Inventor to display sensor readings from an ESP32 microcontroller and control an LED using MQTT (Message Queuing Telemetry Transport) protocol. The open-source MQTT broker, EMQX, is used to facilitate communication between the ESP32 and the app.

## Requirements
- ESP32 development board
- WiFi network access
- MIT App Inventor (http://ai2.appinventor.mit.edu)
- EMQX MQTT Broker (https://www.emqx.io/) 
- MQTT library for MIT AI2 (https://ullisroboterseite.de/android-AI2-MQTT-en.html)

## Setup

### ESP32 and MQTT Configuration
1. Connect the ESP32 to your computer.
2. Use the provided Arduino code to program the ESP32. Modify the code with your WiFi SSID, password, and MQTT broker details.
3. Connect a potentiometer and an MQ2 gas sensor to the ESP32's analog pins or whatever sensor you use.
4. The code reads sensor data and publishes it to MQTT topics ("potentiometer" and "mq2"). Additionally, it subscribes to topics ("redLed" and "greenLed") for controlling LEDs.

### MIT App Inventor Interface
1. Open MIT App Inventor in your browser and create a new project.
2. Design your interface with appropriate components like labels, buttons, and switches.
3. Use MQTT extension components to connect to the EMQX broker and subscribe to the "potentiometer" and "mq2" topics for sensor data.
4. Implement logic to display the received sensor data on the interface.
5. Implement MQTT publishing to the "redLed" and "greenLed" topics based on user interactions with buttons or switches.

## How It Works
1. The ESP32 connects to your WiFi network and the EMQX MQTT broker.
2. It reads sensor values from the potentiometer and MQ2 gas sensor and publishes them to the MQTT topics.
3. The MIT App Inventor interface connects to the same EMQX MQTT broker.
4. It subscribes to the "potentiometer" and "mq2" topics and receives the sensor data.
5. The received data is displayed on the interface in real-time.
6. The interface also enables users to control LEDs by publishing messages to the "redLed" and "greenLed" topics.

## Interface Preview
![App Inventor Interface](/img/interface_preview.png)

## Conclusion
By combining the capabilities of MIT App Inventor, MQTT protocol, and ESP32, you've successfully built an interactive IoT interface. This project demonstrates how to visualize sensor data and remotely control devices using a user-friendly mobile application. The integration of open-source tools like EMQX and App Inventor empowers you to create sophisticated IoT solutions with ease.
