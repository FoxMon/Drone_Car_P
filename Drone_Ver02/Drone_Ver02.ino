#include "Drone.h"

MpuControl mpu = { .address = 0x68, .memory = 0x6b, .gyroOut = 0x43 };
GyroRaw raw;
GyroRawOffset offset;
GyroRawAdj adj;
GyroRate rate;
GyroAngle angle;
Time t;
Throttle throttle = {1}; // userInput -> decide throttle.value 
BalanceForce force;
TargetAngle tAngle;
MotorPin motor_pin = { .pin1 = 3, .pin2 = 4, .pin3 = 5, .pin4 = 6 };
MotorSpeed motor_speed;

void setup() {
    Serial.begin(115200);

    gyro_init(mpu);
    gyro_get(mpu, offset);
    time_init(t);
    // remote_init()
    motor_init(motor_pin);
}

void loop() {
  gyro_read(mpu, raw);
  get_gyro_adj(adj, raw, offset);
  get_gyro_rate(rate, adj);
  time_control(t);
  get_gyro_angle(angle, rate, t);
  get_balance_force(force, tAngle, angle);
  add_balance(force, rate);
  add_balance_angle(force, tAngle, angle, t);
  distribute_motor_speed(motor_speed, throttle, force);
  // remote control check ( Serial or Serial1 -> add userInput )
  motor_output(motor_pin, motor_speed);
}
