#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define POTENTIOMTERPIN 34
#define MQ2PIN 35


char *SSID = "SSID";
char *PWD = "PASSWORD";

// MQTT broker details
char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;


WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);  


void connectToWiFi(char *SSID, char *PWD);
void reconnect();


void setup() {
    Serial.begin(9600);

    pinMode(POTENTIOMTERPIN, INPUT);
    pinMode(MQ2PIN, INPUT);
    
    connectToWiFi(SSID, PWD);
    
    mqttClient.setServer(mqttServer, mqttPort);
}

void loop() {
    if (!mqttClient.connected()) reconnect();

    // Read the analog values from the potentiometer and MQ2 sensor
    char payloadBuffer[10]; 
    snprintf(payloadBuffer, sizeof(payloadBuffer), "%d", analogRead(POTENTIOMTERPIN));

    char payloadBuffer2[10]; 
    snprintf(payloadBuffer2, sizeof(payloadBuffer2), "%d", analogRead(MQ2PIN));

    // Publish the sensor data to MQTT topics
    mqttClient.publish("mohammed/grafana/sensors/potentiometer", payloadBuffer);
    mqttClient.publish("mohammed/grafana/sensors/mq2", payloadBuffer2);
    

    delay(700);
} 

void connectToWiFi(char *SSID, char *PWD) {
  Serial.println("Connectiog to ... ");
 
  WiFi.begin(SSID, PWD);
  Serial.println(SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected.");
  
}

void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
      }
      
  }
}

