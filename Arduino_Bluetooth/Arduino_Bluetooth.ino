#include <UnoWiFiDevEdSerial1.h>

// 2020-03-15
// Bluetooth
// Arduino Bluetooth Module
// Test

void setup(void) {
  Serial1.begin(9600); // Serial1 -> Bluetooth
}

void loop(void) {
  if(Serial1.available()) {
    char userInput = Serial.read();

    Serial.println(userInput);

    if(userInput >= '0' && userInput <= '9') { // read throttle value
      int throttle = (userInput - '0') * 25; // ASCII

      analogWrite(2, throttle);
      analogWrite(3, throttle);
      analogWrite(4, throttle);
      analogWrite(5, throttle);
    }
  }
}
