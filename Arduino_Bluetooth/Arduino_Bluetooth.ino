#include <UnoWiFiDevEdSerial1.h>

// 2020-03-15
// Bluetooth
// Arduino Bluetooth Module
// Test

void setup(void) {
  Serial1.begin(9600); // Serial1 -> Bluetooth
  Serial.begin(9600);
}

void loop(void) {
  if(Serial1.available()) {
//    char userInput = Serial1.read();

    Serial1.println("HelloWorld!");

//    if(userInput >= '0' && userInput <= '9') { // read throttle value
//      int throttle = (userInput - '0') * 25; // ASCII
//    }
  }
}
