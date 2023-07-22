# Node-RED HTTP Server and ESP32 HTTP Client

This project code a simple setup where Node-RED acts as an HTTP server, and an ESP32 microcontroller serves as an HTTP client. The ESP32 sends HTTP GET requests to multiple server URLs, and Node-RED handles the requests and responds accordingly. An additional use case involves an alert LED turning on when an unregistered ID is triggered.

## Node-RED HTTP Server

Node-RED is configured as an HTTP server, and it listens for incoming HTTP GET requests from the ESP32 microcontroller.

### Handling HTTP Requests

When the ESP32 sends HTTP GET requests to the server URLs, Node-RED processes the requests and sends back appropriate responses based on the URLs received.

### Response for Server URLs

1. **http://192.168.146.180:1880/4002190:** The server handles this URL and responds accordingly.

2. **http://192.168.146.180:1880/4200213:** The server handles this URL and responds accordingly.

3. **http://192.168.146.180:1880/4200174:** The server handles this URL and responds accordingly.

### Alert LED 

An alert LED connected to GPIO pin 23 is used for visual indications. It turns on when the server responds with an HTTP error code of 404, indicating that an unregistered ID has been triggered.

## ESP32 HTTP Client

The ESP32 microcontroller acts as an HTTP client and sends HTTP GET requests to the specified server URLs.

### Making HTTP GET Requests

The ESP32 sends HTTP GET requests to the server URLs using the HTTPClient library.

### Handling Server Responses

Upon receiving the server responses, the ESP32 code utilizes the ArduinoJson library to parse JSON data. It extracts relevant information from the JSON and takes actions based on the received data.

