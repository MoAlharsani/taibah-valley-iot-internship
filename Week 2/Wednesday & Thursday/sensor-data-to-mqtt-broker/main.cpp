#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>



char *SSID = "SSID";
char *PWD = "PWASSWORD";

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

int potentiomtrPin = 34;
float voltage;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 




// ====== METHOD DECLARATIONS =======
void setupMQTT();
void reconnect();

void callback(char* topic, byte* payload, unsigned int length);
void connectToWiFi(char *SSID, char *PWD);

void setup() {
    Serial.begin(9600);
    connectToWiFi(SSID, PWD);
    setupMQTT();

    pinMode(potentiomtrPin, INPUT);
}

void loop() {
    if (!mqttClient.connected()) reconnect();
    float voltage = (5.0*analogRead(potentiomtrPin))/4095.0;


    // Create a character array to hold the formatted data
    char data[50];
    
    // Use the snprintf function to format the data into the char array
    snprintf(data, sizeof(data), "voltage coming out of the potentiometer is %.2f", voltage);
    
    // Publish the data to the selected topic
    mqttClient.publish("Test101", data);

} 

void connectToWiFi(char *SSID, char *PWD) {
  Serial.print("Connectiog to ");
 
  WiFi.begin(SSID, PWD);
  Serial.println(SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected.");
  
}

void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(callback);
}

void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe("Test101");
      }
      
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
}
