void setup() {
  // Same as ESP32 baud rate
  Serial.begin(9600);
  delay(100);
}

void loop() {
  if (Serial.available()) {
    String received = Serial.readStringUntil('\n');
    Serial.println(received);
  }

  delay(100);
}
