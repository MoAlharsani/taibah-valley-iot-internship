#include <HardwareSerial.h>

void setup() {
    // Arduino Serial to be set to the same baud rate
    Serial.begin(9600);
    delay(100);
}

void loop()
{
    String mssage = "sent from esp32";
    Serial.println(mssage);
    delay(500);
}