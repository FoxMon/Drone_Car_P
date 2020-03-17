#include "Drone.h"

void get_balance_force(BalanceForce &force, TargetAngle &target, GyroAngle &angle) { // get balance force
  double error_pitch = target.pitch;
  double error_roll = target.roll;
  double error_yaw = target.yaw;

  force.pitch = 1 * error_pitch; // fix 1 -> ex) 0.75, 2, 4
  force.roll = 1 * error_roll;
  force.yaw = 1 * error_yaw;
}

void distribute_motor_speed(MotorSpeed &motorS, Throttle &throttle, BalanceForce &force) { // distribute drone's motor speed
  motorS.pin1_speed = throttle.value + force.roll + force.pitch + force.yaw;
  motorS.pin2_speed = throttle.value + force.roll - force.pitch - force.yaw;
  motorS.pin3_speed = throttle.value + force.roll - force.pitch - force.yaw;
  motorS.pin4_speed = throttle.value - force.roll + force.pitch - force.yaw;

  if(motorS.pin1_speed < 0) { // motor1
    motorS.pin1_speed = 0;
  }
  if(motorS.pin1_speed > 250) {
    motorS.pin1_speed = 250;
  }

  if(motorS.pin2_speed < 0) { // motor2
    motorS.pin2_speed = 0;
  }
  if(motorS.pin2_speed > 250) {
    motorS.pin2_speed = 250;
  }
  
  if(motorS.pin3_speed < 0) { // motor3
    motorS.pin3_speed = 0;
  }
  if(motorS.pin3_speed > 250) {
    motorS.pin3_speed = 250;
  }
  
  if(motorS.pin4_speed < 0) { // motor4
    motorS.pin4_speed = 0;
  }
  if(motorS.pin4_speed > 250) {
    motorS.pin4_speed = 250;
  }

  if(throttle.value == 0) { // If throttle value is 0, Drone's speed is 0
    motorS.pin1_speed = 0;
    motorS.pin2_speed = 0;
    motorS.pin3_speed = 0;
    motorS.pin4_speed = 0;
  }
}

void add_balance(BalanceForce &force, GyroRate &rate) {
  force.roll += 1 * ( -rate.roll );
  force.pitch += 1 * ( -rate.pitch );
  force.yaw += 1 * ( -rate.yaw );
}

void add_balance_angle(BalanceForce &force, TargetAngle &target, GyroAngle &angle, Time &t) {
  static double result_force_pitch;
  static double result_force_roll;
  static double result_force_yaw;

  double error_pitch = target.pitch - angle.pitch;
  double error_roll = target.roll - angle.roll;
  double error_yaw = target.yaw - angle.yaw;

  result_force_pitch = 1 * error_pitch * t.period;
  result_force_roll = 1 * error_roll * t.period;
  result_force_yaw = 1 * error_yaw * t.period;

  extern Throttle throttle;

  if(throttle.value == 0) {
    result_force_pitch = 0;
    result_force_roll = 0;
    result_force_yaw = 0;
  }

  force.pitch += result_force_pitch;
  force.roll += result_force_roll;
  force.yaw += result_force_yaw;
}
