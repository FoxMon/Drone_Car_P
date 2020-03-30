#include "Drone.h"
#include <Wire.h>

void gyro_init(MpuControl& mpu) { // Wire init set
  Wire.begin();
  Wire.beginTransmission(mpu.address);
  Wire.write(mpu.memory);
  Wire.write(0);
  Wire.endTransmission(true);
}

void gyro_read(MpuControl& mpu, GyroRaw& raw) { // read from mpu
  Wire.beginTransmission(mpu.address);
  Wire.write(mpu.memory);
  Wire.endTransmission(false);
  Wire.requestFrom(mpu.address, 6, true);

  raw.x = Wire.read() <<8 | Wire.read();
  raw.y = Wire.read() <<8 | Wire.read();
  raw.z = Wire.read() <<8 | Wire.read();
}

void gyro_get(MpuControl& mpu, GyroRawOffset& gyroOffset) { // get gyro
  int32_t sumGyX = 0, sumGyY = 0, sumGyZ = 0;
  GyroRaw gyroraw = { 0 };

  for(int i = 0; i < 1000; i++) {
    gyro_read(mpu, gyroraw);

    sumGyX += gyroraw.x;
    sumGyY += gyroraw.y;
    sumGyZ += gyroraw.z;

    delay(1);
  }

  gyroOffset.x = (double)sumGyX / 1000;
  gyroOffset.y = (double)sumGyY / 1000;
  gyroOffset.z = (double)sumGyZ / 1000;
}

void time_init(Time& t) { // time set init
  t.previous = micros();
}

void time_control(Time& t) { // calcurate time
  t.now = micros();
  t.period = (t.now - t.previous) / 1000000.0;
  t.previous = t.now;
}

void get_gyro_adj(GyroRawAdj &adj, GyroRaw &raw, GyroRawOffset &offset) { // get adj
  adj.x = raw.x - offset.x;
  adj.y = raw.y - offset.y;
  adj.z = raw.z - offset.z;
}

void get_gyro_rate(GyroRate &rate, GyroRawAdj &adj) { // get rate
  rate.pitch = adj.x / 131.0;
  rate.roll = adj.y / 131.0;
  rate.yaw = adj.z / 131.0;
}

void get_gyro_angle(GyroAngle &angle, GyroRate &rate, Time &t) { // get angle
  angle.pitch += rate.pitch * t.period;
  angle.roll += rate.roll * t.period;
  angle.yaw += rate.roll * t.period;

  extern Throttle throttle;

  if(throttle.value == 0) {
    angle.pitch = 0;
    angle.roll = 0;
    angle.yaw = 0;
  }
}
