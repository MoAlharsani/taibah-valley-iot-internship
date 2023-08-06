#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>



char *SSID = "SSID";
char *PWD = "PWD";

char *mqttServer = "broker.emqx.io";
int mqttPort = 1883;

int potentiomtrPin = 35;
int mq2Pin = 34;
int redLedPin = 14;
int greenLedPin = 12;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 



void setupMQTT();
void reconnect();

void callback(char* topic, byte* payload, unsigned int length);
void connectToWiFi(char *SSID, char *PWD);
void ledHandling(char* topic, String message);
void publishReading();

void setup() {
    Serial.begin(9600);
    connectToWiFi(SSID, PWD);
    setupMQTT();


    pinMode(potentiomtrPin, INPUT);
    pinMode(mq2Pin, INPUT);
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
}

void loop() {
    if (!mqttClient.connected()) reconnect();
    mqttClient.loop();

    publishReading();
    delay(500);
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
        mqttClient.subscribe("redLed");
        mqttClient.subscribe("greenLed");
      }
      
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  Serial.print("Received: Topic - ");
  Serial.print(topic);
  Serial.print(": ");
  
  for (int i = 0; i < length; i++) {
    message += ((char)payload[i]);
  }
  Serial.println(message);
  if((strcmp(topic, "greenLed") == 0)||(strcmp(topic, "redLed") == 0)){
    ledHandling(topic, message);
  }

}

void ledHandling(char* topic, String message) {

  if (strcmp(topic, "greenLed") == 0) {
    if (message == "1") {
      digitalWrite(greenLedPin, HIGH);
      return;
    }
    if (message == "0") {
      digitalWrite(greenLedPin, LOW);
      return;
    }
  }

  if (strcmp(topic, "redLed") == 0) {
    if (message == "1") {
      digitalWrite(redLedPin, HIGH);
      return;
    }
    if (message == "0") {
      digitalWrite(redLedPin, LOW);
      return;
    }
  }
}

void publishReading(){
  // Create a character array to hold the formatted data
  char potentiometer[50];
  char mq2[50];
    
  // Use the snprintf function to format the data into the char array
  snprintf(potentiometer, sizeof(potentiometer), "%d", analogRead(potentiomtrPin));
  snprintf(mq2, sizeof(mq2), "%d", analogRead(mq2Pin));
  delay(2000);

  // Publish the data to the selected topic
  mqttClient.publish("potentiometer", potentiometer);
  mqttClient.publish("mq2", mq2);
}
