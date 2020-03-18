#ifndef DRONE__H__
#define DRONE__H__ 

typedef struct { // Motor pin control
  int pin1;
  int pin2;
  int pin3;
  int pin4;
} MotorPin;

typedef struct { // Motor output speed
  double pin1_speed;
  double pin2_speed;
  double pin3_speed;
  double pin4_speed;
} MotorSpeed;

typedef struct { // Mpu control
  int address;
  int memory;
  int gyroOut;
} MpuControl;

typedef struct { // Gyro x, y, z
  int16_t x;
  int16_t y;
  int16_t z;
} GyroRaw;

typedef struct { // GyroOffset x, y, z
  int16_t x;
  int16_t y;
  int16_t z;
} GyroRawOffset;

typedef struct { // Gyro fix
  int16_t x;
  int16_t y;
  int16_t z;
} GyroRawAdj;

typedef struct { // Gyro rate
  double roll;
  double pitch;
  double yaw;
} GyroRate; 

typedef struct { // Gyro angle
  double roll;
  double pitch;
  double yaw;
} GyroAngle;

typedef struct { // target angle
  double roll;
  double pitch;
  double yaw;
} TargetAngle;

typedef struct { // force == amplifier
  double roll;
  double pitch;
  double yaw;
} BalanceForce;

typedef struct { double value; } Throttle; // Throttle value

typedef struct { // Time control
  uint32_t now;
  uint32_t previous;
  double period;
} Time;

#endif
