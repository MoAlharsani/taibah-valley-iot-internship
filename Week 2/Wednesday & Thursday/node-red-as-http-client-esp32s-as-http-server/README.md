# ESP32 Webserver and Node-RED HTTP Client

This code demonstrates a simple setup using an ESP32 microcontroller as a web server and Node-RED as an HTTP client. The ESP32 hosts a basic web page and provides API endpoints to control an LED, a buzzer, and read values from a potentiometer.

## ESP32 Web Server

### Accessing the Web Server

Connect your device to the ESP32's Wi-Fi network using the credentials "ESP32-Access-Point" and "11223344." Access the web page served by the ESP32 by entering "http://192.168.4.1/" in a web browser.

### Potentiometer Reading

When Node-RED sends an HTTP GET request to the "/potentiometer" endpoint, the ESP32 reads the potentiometer value from GPIO pin 35 and sends it back in the HTTP response.

## Node-RED HTTP Client

### Reading Potentiometer

In the Node-RED workspace, use an HTTP Request node and set the URL to "http://192.168.4.1/potentiometer." When triggered, Node-RED will send the HTTP GET request to the ESP32's API endpoint and receive the potentiometer reading in the HTTP response.

### Controlling LED and Buzzer

To control the LED, use an HTTP Request node with the URL "http://192.168.4.1/red-light-on" to turn it on. For the buzzer, use the URL "http://192.168.4.1/buzzer-on" to activate it. The ESP32 will respond accordingly, and the LED and buzzer will be controlled as requested.
