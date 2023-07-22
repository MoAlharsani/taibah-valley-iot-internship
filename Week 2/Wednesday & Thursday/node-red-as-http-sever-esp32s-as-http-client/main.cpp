#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

const char *SSID = "OnePlus 6T";
const char *PWD = "12345@MM";

// serverUrls[1] is not on node-red, so it will turn led on for alerting
const char* serverUrls[] = {
  "http://192.168.146.180:1880/4002190", // check if the ip have changed
  "http://192.168.146.180:1880/4200213",
  "http://192.168.146.180:1880/4200174"
};




int alertLED = 23;

void connectToWiFi(const char* SSID, const char* PWD);
void httpGetRequest(HTTPClient& http, const char* serverUrl);
void handleData(const String& data);

void setup() {
  Serial.begin(9600);
  pinMode(alertLED, OUTPUT);
  WiFi.disconnect();
  connectToWiFi(SSID, PWD);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    for(int i=0;i<3;i++){
      httpGetRequest(http, serverUrls[i]);
      delay(1000);
    }
  }

  // Wait for some time before making the next request
  delay(5000);
}

void connectToWiFi(const char* SSID, const char* PWD) {
  Serial.print("Connecting to ");
  WiFi.begin(SSID, PWD);
  Serial.println(SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected.");
}

void handleData(const String& data) {
  // Create a JSON object to parse the data
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, data);

  // Check if parsing the JSON was successful
  if (error) {
    Serial.println("JSON parsing failed!");
    return;
  }

  // Extract data from the JSON object
  int id = doc["id"];
  const char* name = doc["name"];
  int age = doc["age"];
  const char* city = doc["city"];

  // Do something with the extracted data (you can also store it or send it to other devices, etc.)
  Serial.println("Received Data:");
  Serial.print("ID: ");
  Serial.println(id);
  Serial.print("Name: ");
  Serial.println(name);
  Serial.print("Age: ");
  Serial.println(age);
  Serial.print("City: ");
  Serial.println(city);
}

void httpGetRequest(HTTPClient& http, const char* serverUrl) {
  // Make an HTTP GET request to the server
  http.begin(String(serverUrl));
  int httpResponseCode = http.GET();

  if (httpResponseCode == HTTP_CODE_OK) {
    String payload = http.getString();
    digitalWrite(alertLED, LOW);
    // Handle the received data here
    handleData(payload);
  } else {
    Serial.print("HTTP Request failed with error code: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode == 404) digitalWrite(alertLED, HIGH);
  }
  http.end();
}
