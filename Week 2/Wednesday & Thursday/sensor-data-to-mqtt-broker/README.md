# Sending Sensor Data through MQTT with ESP32

This project demonstrates how to use an ESP32 microcontroller to send sensor data through MQTT to the broker.hivemq.com MQTT broker.

## ESP32 Code

The ESP32 is set up as an MQTT publisher, reading data from a potentiometer connected to pin 34.

### Setup

- The ESP32 connects to the Wi-Fi network using the provided SSID and password.
- The setupMQTT() function is called to configure the MQTT client with the broker's address and port.
- The potentiometer is set as an input pin.

### Loop

- In the loop(), the ESP32 checks if it is connected to the MQTT broker. If not, it attempts to reconnect.
- The ESP32 reads the voltage from the potentiometer and formats it into a character array.
- The formatted data is then published to the MQTT topic "Test101" on the broker.hivemq.com.

### MQTT Callback

- The ESP32 subscribes to the topic "Test101" using the same MQTT client.
- When a message is received on the subscribed topic, the callback function is triggered, and the received message is printed to the serial monitor.

Ensure that the ESP32 is connected to the broker.hivemq.com MQTT broker. The ESP32 will publish the potentiometer voltage data to the "Test101" topic.
