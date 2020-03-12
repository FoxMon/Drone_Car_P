#include <Servo.h>

const int servo_pin = 10;
Servo auto_car_direction;

void Servo_Setup(){
  auto_car_direction.attach(servo_pin);
  Car_Direction_Flort();
}

void Car_Direction_Flort(){
  auto_car_direction.write(90);
}

void Car_Direction_Left(){
  auto_car_direction.write(30);
}

void Car_Direction_Right(){
  auto_car_direction.write(150);
}
