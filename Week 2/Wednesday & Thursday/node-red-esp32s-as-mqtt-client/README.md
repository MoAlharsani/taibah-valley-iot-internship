# ESP32 and Node-RED as MQTT Clients

This code demonstrates bidirectional MQTT communication between an ESP32 microcontroller and Node-RED using the broker.hivemq.com MQTT broker.

## ESP32 Code

The ESP32 is set up as an MQTT publisher and subscriber.

### Publisher

- The ESP32 connects to the Wi-Fi network using the provided SSID and password.
- It sets up an MQTT client using the PubSubClient library and connects to the broker.hivemq.com MQTT broker.
- In the loop(), the ESP32 publishes the message "Mohammed" to the MQTT topic "Test101" every 5 seconds.

### Subscriber

- The ESP32 subscribes to the topic "Test101" using the same MQTT client.
- When a message is received on the subscribed topic, the callback function is triggered, and the received message is printed to the serial monitor.

## Node-RED Flow

Node-RED is set up as a separate MQTT publisher and subscriber, using the same broker.hivemq.com MQTT broker.

### Publisher

- Node-RED connects to the MQTT broker on broker.hivemq.com.
- The flow includes an inject node that publishes the payload "mohammed" to the topic "Test101" on the broker every time it is triggered.

### Subscriber

- Node-RED subscribes to the topic "Test101" and receives messages from the broker.
- The received payload is displayed in the debug node named "debug 1."

Both the ESP32 and Node-RED can publish and subscribe independently to the broker.hivemq.com MQTT broker, allowing bidirectional communication between the two devices. The ESP32 will publish the message "Mohammed" to the topic "Test101," and Node-RED will receive and display the payload in the debug window.

Make sure both the ESP32 and Node-RED are connected to the broker.hivemq.com MQTT broker with appropriate topic configurations to observe the bidirectional communication.
