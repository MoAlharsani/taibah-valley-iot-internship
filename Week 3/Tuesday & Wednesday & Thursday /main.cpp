#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <secret.h>


#define POTENTIOMTERPIN 34
#define MQ2PIN 35

const char AWS_IOT_ENDPOINT[] = "xxxxxxxxxxx-ats.iot.eu-west-3.amazonaws.com"; // change it to your end-point aws address
#define THINGNAME "potentiometer"
#define AWS_IOT_SUBSCRIBE_TOPIC "moalharsani/aws"


char *SSID = "SSID"; 
char *PWD = "PWD";



WiFiClientSecure wifiClient = WiFiClientSecure();
PubSubClient mqttClient(wifiClient);  


void connectWifi();
void connectAWS();
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
    Serial.begin(9600);

    pinMode(POTENTIOMTERPIN, INPUT);
    pinMode(MQ2PIN, INPUT);

    connectWifi();
    connectAWS();
}

void loop() {
    mqttClient.loop();

    // Read the analog values from the potentiometer and MQ2 sensor
    char payloadBuffer[10]; 
    snprintf(payloadBuffer, sizeof(payloadBuffer), "%d", analogRead(POTENTIOMTERPIN));

    char payloadBuffer2[10]; 
    snprintf(payloadBuffer2, sizeof(payloadBuffer2), "%d", analogRead(MQ2PIN));

    // Publish the sensor data to MQTT topics
    mqttClient.publish("mohammed/aws/sensors/potentiometer", payloadBuffer);
    mqttClient.publish("mohammed/aws/sensors/mq2", payloadBuffer2);
    
    delay(700);
} 

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PWD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}


void connectAWS() {
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  wifiClient.setCACert(AWS_CERT_CA);
  wifiClient.setCertificate(AWS_CERT_CRT);
  wifiClient.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  mqttClient.setServer(AWS_IOT_ENDPOINT, 8883);

  // Create a message handler
  mqttClient.setCallback(callback);

  Serial.println("Connecting to AWS IOT..");

  while (!mqttClient.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if (!mqttClient.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  mqttClient.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Callback - ");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
}
