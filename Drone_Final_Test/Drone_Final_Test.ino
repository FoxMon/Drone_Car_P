// Rotation Speed
// Final Test
// Roll, Pitch, Yaw
// 2020-03-14
// Check for Drone's motor speed and add Controll

#include <Wire.h>

int throttle = 0; // amplifier

void setup() {
  Serial.begin(115200);

  Wire.begin();
  Wire.setClock(400000);

  Wire.beginTransmission(0x68);
  Wire.write(0x6b);
  Wire.write(0x0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(0x68);
  // Wire.write(0x45);
  Wire.write(0x43);
  Wire.endTransmission(false);
  // Wire.requestFrom(0x68, 2, true);
  Wire.requestFrom(0x68, 6, true);

  int16_t GyXH = Wire.read();
  int16_t GyXL = Wire.read();
  int16_t GyYH = Wire.read(); // read sensor
  int16_t GyYL = Wire.read();
  int16_t GyZH = Wire.read();
  int16_t GyZL = Wire.read();

  int16_t GyX = GyXH << 8|GyYL;
  int16_t GyY = GyYH << 8|GyYL;
  int16_t GyZ = GyZH << 8|GyYL;

  static int32_t GyXSum = 0;
  static int32_t GyYSum = 0;
  static int32_t GyZSum = 0;
  
  static double GyXOff = 0.0;
  static double GyYOff = 0.0;
  static double GyZOff = 0.0;
  
  static int sample = 1000; // count loop

  if(sample > 0) {
    GyXSum += GyX;
    GyYSum += GyY;
    GyZSum += GyZ;
    sample--;

    if(sample == 0) {
      GyXOff = GyXSum / 1000.0;
      GyYOff = GyYSum / 1000.0;
      GyZOff = GyZSum / 1000.0;
    }

    delay(1);
    
    return;
  }

  double GyXresult = GyX - GyXOff; 
  double GyYresult = GyY - GyYOff; 
  double GyZresult = GyZ - GyZOff; 
  double GyXR = GyXresult / 131;
  double GyYR = GyYresult / 131;
  double GyZR = GyZresult / 131;

  static unsigned long t_prev = 0;
  unsigned long t_now = micros();
  double dt = (t_now - t_prev) / 1000000.0;
  t_prev = t_now;

  static double AngleX = 0.0;
  static double AngleY = 0.0;
  static double AngleZ = 0.0;
  
  AngleX += GyXR * dt;
  AngleY += GyYR * dt;
  AngleZ += GyZR * dt;

  static double tAngleX = 0.0;
  static double tAngleY = 0.0;
  static double tAngleZ = 0.0;
  
  double eAngleX = tAngleX - AngleX;
  double eAngleY = tAngleY - AngleY;
  double eAngleZ = tAngleZ - AngleZ;
  double Kp = 1.0;
  double BalX = Kp * eAngleX;
  double BalY = Kp * eAngleY;
  double BalZ = Kp * eAngleZ;
  double Kd = 1.0;
  
  BalX += Kd *- GyXR;
  BalY += Kd *- GyYR;
  BalZ += Kd *- GyZR;

  if(throttle == 0) {
    BalX = BalY = BalZ = 0.0;
  }

// For soft flight

  double Ki = 1.0; // change Ki value ex) 0.5 , 1.5 , 2 etc...
  static double ResX = 0.0, ResY = 0.0, ResZ = 0.0;

  ResX += Ki * eAngleX * dt;
  ResY += Ki * eAngleY * dt;
  ResZ += Ki * eAngleZ * dt;

  if(throttle == 0) {
    ResX = ResY = ResZ = 0.0;
  }

  BalX += ResX;
  BalY += ResY;
  BalZ += ResX;

  if(Serial.available() > 0) { // Bluetooth -> Serial1
    while(Serial.available() > 0){
      char userInput = Serial.read();

      if(userInput >= '0' && userInput <= '9'){
        throttle = (userInput - '0') * 25;
      } else if(userInput == 'a'){ // Left
      // tAngleY = -10.0;
      } else if(userInput == 'd'){ // Right
      // tAngleY = 10.0;
      } else if(userInput == 's') { // Balance
      // tAngleX = tAngleY = 0.0;
      } else if(userInput == 'w') { // Forward
      // tAngleX = -10.0;
      }
    }
  }

  double speedA = throttle + BalY + BalX + BalZ;
  double speedB = throttle - BalY + BalX - BalZ;
  double speedC = throttle - BalY - BalX + BalZ;
  double speedD = throttle + BalY - BalX - BalZ;
  int iSpeedA = constrain((int)speedA, 0, 250);
  int iSpeedB = constrain((int)speedB, 0, 250);
  int iSpeedC = constrain((int)speedC, 0, 250);
  int iSpeedD = constrain((int)speedD, 0, 250);

  analogWrite(10, iSpeedA);
  analogWrite(11, iSpeedB);
  analogWrite(12, iSpeedC);
  analogWrite(13, iSpeedD);

  Serial.println(BalY);
  Serial.println(BalX);
  
  

//Serial.print("throttle : ");
//Serial.println(throttle);
//Serial.print("iSpeedA : ");
//  Serial.println(iSpeedA);
//  Serial.print("iSpeedC : ");
//  Serial.println(iSpeedB);
}
