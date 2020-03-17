#include <PinChangeInterrupt.h>
#include <Servo.h>

#define LIMIT 600
#define BRIGHT 200

const int trig = 8;
const int echo = 9;
const int buzzer_pin = 10;
const int servo_pin = 11;

Servo auto_car_direction;

unsigned long distance = 50;
static const int what_thing = 15; //cm

bool speak_buzzer = false;
bool changed_distance = false; //거리 바뀜
bool emergency_now = false; //긴급상황 돌입

enum { // enum of LEDs
  FRONTLEDON = 'Q',
  FRONTLEDOFF = 'q',
  REARLEDON = 'W',
  REARLEDOFF = 'w',
  ALLLEDON = 'E',
  ALLLEDOFF = 'e',
  REARLEFTBLINK = 'R',
  REARRIGHTBLINK = 'r',
};

enum { // enum of Drive
  AUTODRIVE = 'O',
 // MANUAL = 'o',
};

enum { // enum of Drive Order for Serial
  GO = 'g',
  BACK = 'b',
  LEFT = 'l',
  RIGHT = 'x',
  STOP = 's',
  GOANDLEFT = 'u',
  GOANDRIGHT = 'i',
  BACKANDLEFT = 'y',
  BACKANDRIGHT = 't',
};

enum { // enum of Drive Order for Bluetooth
  GO_B = 'G',
  BACK_B = 'B',
  LEFT_B = 'L',
  RIGHT_B = 'X',
  STOP_B = 'S',
  GOANDLEFT_B = 'U',
  GOANDRIGHT_B = 'I',
  BACKANDLEFT_B = 'Y',
  BACKANDRIGHT_B = 'T',
};

enum { // enum of Speed
  SPEED0 = '0',
  SPEED1 = '1',
  SPEED2 = '2',
  SPEED3 = '3',
};

bool rear_left_led_flag = false; // Rear Blink Led Flag
bool rear_right_led_flag = false;
bool rear_left_blink = false;
bool rear_right_blink = false;
bool change_led_on_off = false; // Change Led On/Off Flag
bool blink_led_on_off = false; // Blink Led
bool control_change = false; // Check Control Change
bool auto_drive_check = false; // Auto Drive Check
bool change_drive_action = false; // Check drive action
bool change_drive_speed =false; // Check drive speed

char change_led = ALLLEDOFF; // Initial ALLLEDOFF
char blink_led; // Blink Led
char remote_read; // Read User Input for control
char run_drive = STOP; // Run drive!
char drive_speed = SPEED0; // Drive Speed

const int front_left_led = 2; // Front Left Led
const int front_right_led = 3; // Front Right Led
const int rear_left_led = 4; // Rear Left Led
const int rear_right_led = 5; // Rear Right Led
const int dirA = 10; // Left Motor
const int dirB = 7; // Right Motor
const int pwmA = 0;
const int pwmB = 0;

int bright_value; // Read Bright Value
int initial_bright = ALLLEDOFF; // Initial Set_up LED status by brightness
bool bright_flag = false; // Bright Flag

// unsigned int accel;

void setup(void) {
  Motor_SetUp();
  Remote_Control_Set();
  Led_Set_Up();
  Buzzer_Setup();
  Servo_Setup();
  Distance_Setup();
}

void loop(void) {
  Motor_Loop();
  Remote_Control_Loop();
  Led_Loop();
  Distance_Loop();
  Buzzer_Loop();
}
