#include <Arduino.h>
#include <WiFi.h>

int REDLED = 22;
int BUZZER = 23;
int POTENTIOMETER = 35;


// ESP32s AP network credentials
char* ssid = "ESP32-Access-Point";
char* pwd = "11223344";

WiFiServer server(80);

void handleHomePage(WiFiClient client);
void handlePotentiometer(WiFiClient client);


void espAsAccessPoint(char* ssid, char* password);




void setup() {
  Serial.begin(9600);

  // Setting the esp32s as an access point
  espAsAccessPoint(ssid, pwd);
  pinMode(REDLED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  server.begin();

}


void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client connected!");

    // Read the request until there's no data available (up to a maximum length)
    String request = "";
    while (client.connected() && !client.available()) {
      delay(1);
    }
    while (client.available()) {
      char c = client.read();
      request += c;
      if (request.length() >= 100) {
        // Avoid reading large requests to prevent memory issues
        break;
      }
    }

    // Check if it's a GET request (assuming the first line contains the request method)
    if (request.startsWith("GET")) {
      // Extract the URL from the request
      int urlStart = request.indexOf(' ') + 1;
      int urlEnd = request.indexOf(' ', urlStart);
      String url = request.substring(urlStart, urlEnd);
      Serial.println(url);


      // Use a switch statement to handle different URLs
      // Call the appropriate handler function based on the URL
      // For unknown URLs, use the default case for 404 Not Found response.
      switch (url[1]) {
        case '\0': // URL "/"
          handleHomePage(client);
          break;
        case 'r': // URL "/red-light-on"
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println(""); // Important: add a blank line to end the headers
          client.println("<h1> RED LIGHT IS ON </h1>");
          digitalWrite(REDLED, HIGH);
          break;
        case 'b': // URL "buzzer-on"
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println(""); // Important: add a blank line to end the headers
          client.println("<h1> BUZZER IS ON </h1>");
          digitalWrite(BUZZER, HIGH);
          break;
        case 'p': // URL "potentiometer"
          handlePotentiometer(client);
          break;
        // Add more cases for other URLs if needed
        default:
          // For unknown URLs, send a 404 Not Found response
          client.println("HTTP/1.1 404 Not Found");
          client.println("Content-Type: text/html");
          client.println(""); // Important: add a blank line to end the headers
          client.println("<h1>404 Not Found</h1>");
          break;
      }

      // Close the connection
      client.stop();
      Serial.println("Client disconnected.");
    }
  }
}


void espAsAccessPoint(char* ssid, char* password){
  WiFi.disconnect();

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");

  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

}



// Server responses as HTML

void handleHomePage(WiFiClient client) {
  // Send the HTTP response (Root ip/)
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>Hello from ESP32!</title>");
    client.println("<style>");
    client.println("body { font-family: Arial, sans-serif; margin: 40px; }");
    client.println("h1 { color: #007BFF; }");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>Hello from ESP32!</h1>");
    client.println("<p>This is the Root page</p>");
    client.println("</body>");
    client.println("</html>");
}

void handlePotentiometer(WiFiClient client) {
  // Send the HTTP response (/X)
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // Important: add a blank line to end the headers
    client.println("<h1> potentiometer reading is </h1>");
    client.println(analogRead(POTENTIOMETER));
}

