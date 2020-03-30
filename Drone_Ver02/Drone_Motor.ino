#include "Drone.h"

void motor_init(MotorPin& motor) { // set motor
  pinMode(motor.pin1, OUTPUT);
  pinMode(motor.pin2, OUTPUT);
  pinMode(motor.pin3, OUTPUT);
  pinMode(motor.pin4, OUTPUT);

  analogWrite(motor.pin1, 0);
  analogWrite(motor.pin2, 0);
  analogWrite(motor.pin3, 0);
  analogWrite(motor.pin4, 0);
}

void motor_output(MotorPin& motor, MotorSpeed& motorS) { // motor output
  analogWrite(motor.pin1, motorS.pin1_speed);
  analogWrite(motor.pin1, motorS.pin2_speed);
  analogWrite(motor.pin1, motorS.pin3_speed);
  analogWrite(motor.pin1, motorS.pin4_speed);
}
