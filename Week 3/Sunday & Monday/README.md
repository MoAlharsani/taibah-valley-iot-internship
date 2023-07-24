# Sending Sensor Data to Cloud and Displaying on Dashboard using MQTT

## Overview
This IoT code demonstrates how to send sensor data from an ESP32 microcontroller to the cloud using MQTT (Message Queuing Telemetry Transport) protocol. The MQTT broker, `broker.hivemq.com`, is utilized for this purpose.

## Hardware Requirements
- ESP32 development board
- Potentiometer (analog sensor)
- MQ2 Gas Sensor (analog sensor)

## Software Requirements
- Arduino IDE (https://www.arduino.cc/en/software)
- WiFi library for Arduino (already included in Arduino IDE)
- PubSubClient library for Arduino (https://github.com/knolleary/pubsubclient)

## Setup
1. Connect the potentiometer to pin 34 of the ESP32 and the MQ2 gas sensor to pin 35.

2. Configure the Wi-Fi credentials by replacing the placeholders `SSID` and `PASSWORD` with your Wi-Fi network name and password in the Arduino sketch.

3. Install the required libraries in the Arduino IDE:
   - WiFi library: Go to **Sketch > Include Library > WiFi**.
   - PubSubClient library: Download it from the link provided above and install it by going to **Sketch > Include Library > Add .ZIP Library**.

4. Upload the Arduino sketch to the ESP32 board.

## How It Works
1. The ESP32 connects to the specified Wi-Fi network using the provided credentials.

2. After establishing a Wi-Fi connection, the ESP32 connects to the MQTT broker `broker.hivemq.com` on port 1883.

3. The ESP32 reads analog values from the potentiometer and MQ2 gas sensor.

4. The sensor data is converted to a string format and published to the MQTT broker on two different topics: `"mohammed/grafana/sensors/potentiometer"` and `"mohammed/grafana/sensors/mq2"`.

5. Grafana Cloud, or any other MQTT subscriber, can subscribe to these topics and receive the sensor data.

## Dashboard Visualization
You can use Grafana to create a dashboard and visualize the sensor data received from the MQTT broker. Follow these steps:

1. Sign up for a free account on Grafana Cloud (https://grafana.com/).

2. Create a new data source in Grafana and set it to subscribe to the MQTT broker (in this case, `broker.hivemq.com` on port 1883).

3. Create a new dashboard and add panels to display the sensor data received from the topics `"mohammed/grafana/sensors/potentiometer"` and `"mohammed/grafana/sensors/mq2"`.

4. Customize the dashboard with graphs, charts, or other visualizations as per your requirements.

5. The dashboard will now show real-time sensor data received from the ESP32 via MQTT.
