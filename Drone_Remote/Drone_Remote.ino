#include <Wire.h>

int throttle = 0; // read motor speed

void setup() {
  // Same Code
}

void loop() {
  // Same

  if(Serial.available() > 0) {
    char userInput = Serial.read();

    if(userInput >= '0' && userInput <= '9') {
      throttle = ( userInput - '0' ) * 25;
    } else if(userInput == 'a'){ // Left
      // tAngleY = -10.0;
    } else if(userInput == 'd'){ // Right
      // tAngleY = 10.0;
    } else if(userInput == 's') { // Balance
      // tAngleY = 0.0;
    }
  }
}
