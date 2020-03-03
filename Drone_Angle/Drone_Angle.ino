// Angle
// Test
// Only Roll
// 2020-03-02

#include <Wire.h> // I2C

int throttle = 0; // amplifier

void setup() {
  Serial.begin(115200);

  Wire.begin(); // Start I2C
  Wire.setClock(400000);

  Wire.beginTransmission(0x68); // start transmission
  Wire.write(0x6b);
  Wire.write(0x0);
  Wire.endTransmission(true); // end transmission 
}

void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0x45);
  Wire.endTransmission(false); // restart
  Wire.requestFrom(0x68, 2, true);  

  int16_t GyYH = Wire.read(); // read sensor
  int16_t GyYL = Wire.read();
  int16_t GyY = GyYH << 8|GyYL;

  /*
  * GyY -> 0 
  * +-0 average.
  */

  static int32_t GyYSum = 0;
  static double GyYOff = 0.0;
  static int sample = 1000;

  if(sample > 0) {
    GyYSum += GyY;
    sample--;

    if(sample == 0) {
      GyYOff = GyYSum / 1000;
    }

    delay(1);
    
    return;
  }

  double GyYresult = GyY - GyYOff; 
  double GyYRoll = GyYresult / 131;

  static unsigned long t_prev = 0;
  unsigned long t_now = micros();
  double dt = (t_now - t_prev) / 1000000.0;
  t_prev = t_now;

  static double AngleY = 0.0;
  AngleY += GyYRoll * dt;

  if(throttle == 0){
    AngleY = 0.0;
  }

  static double tAngleY = 0.0;
  double eAngleY = tAngleY - AngleY;
  double Kp = 1.0;
  double BalY = Kp * eAngleY;

  if(Serial.available() > 0){ // Bluetooth -> Serial1
    while(Serial.available() > 0){
      char userInput = Serial.read();

      if(userInput >= '0' && userInput <= '9'){
        throttle = (userInput - '0') * 25;
      }
    }
  }

  double speedA = throttle + BalY; // motor A ~ D logic
  double speedB = throttle - BalY;
  double speedC = throttle - BalY;
  double speedD = throttle + BalY;
  int iSpeedA = constrain((int)speedA, 0, 255);
  int iSpeedB = constrain((int)speedB, 0, 255);
  int iSpeedC = constrain((int)speedC, 0, 255);
  int iSpeedD = constrain((int)speedD, 0, 255);

  analogWrite(10, iSpeedA);
  analogWrite(11, iSpeedB);
  analogWrite(12, iSpeedC);
  analogWrite(13, iSpeedD);
  
  // static int cnt_loop;

  // cnt_loop++;

  // if((cnt_loop % 100) != 0){
  //  return;
  // }

  // Serial.print("GyY = ");
  // Serial.print(GyY);
  // Serial.print("GyYresult = ");
  // Serial.print(GyYresult);
  // Serial.println();
}
