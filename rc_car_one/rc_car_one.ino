#include <PinChangeInterrupt.h>
#include <Servo.h>
////////////////////////////////////////////////////////////////
const int trig = 8;
const int echo = 9;

unsigned long distance = 50;
static const int what_thing = 15; //cm
////////////////////////////////////////////////////////////////
void setup(){
  Distrance_Setup();
  Buzzer_Setup();
  Servo_Setup();
}

void loop(){
  Distance_Loop();
  Buzzer_Loop();
}
////////////////////////////////////////////////////////////////

bool changed_distance = false; //거리 바뀜
bool emergency_now = false; //긴급상황 돌입


void Distrance_Setup() {
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);

attachPCINT(digitalPinToPCINT(echo), EchoIsr, CHANGE);
}

void Distance_Loop(){
  Distance_Checking();
  Emergency_Checking();
  //void Emergency_Car_Move();
}


void EchoIsr (void){
  static volatile unsigned long start_echo = 0;
  static volatile unsigned long end_echo = 0;

  unsigned int echo_pin_on = digitalRead(echo);

  if(echo_pin_on == HIGH){
    start_echo = micros();
  }
  else{
    end_echo = micros();
    unsigned long duration = end_echo - start_echo;
    distance = duration / 58;
    changed_distance = true;
  }
}

void Distance_Checking(){
  static unsigned long prev_time = 0;
  const unsigned long interval_time = 20;

  unsigned long curr_time = millis();
  if(curr_time - prev_time >= interval_time){
    prev_time = curr_time;

    
    if(emergency_now) return; //비상이면 나감

    
    Ultrasonic_Sensor();      //초음파 시작
  }
     
}

void Ultrasonic_Sensor(){ //초음파 온
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
}

void Emergency_Checking(){ //거리별 위험도격상
  
  if(changed_distance){
    changed_distance = false;

    static int level = 0;
    if(distance <= what_thing){
      level++;

      if(level == 10){
        level = 0;

        emergency_now = true;
      }     
    }
    else{
      if(level > 0){
        level--;
      }
    }
  }
}

//void Emergency_Car_Move(){
//
//  if(emergency_now){
//    emergency_now = false;
//
//    //1. @@@@
//    //2. @@@@
//  }
//}
///////////////////////////////////////////////////////////////부저
const int buzzer_pin = 10;

bool speak_buzzer = false;

void Buzzer_Setup() {
pinMode(buzzer_pin, OUTPUT);
}

void Buzzer_Loop() {
   Buzzer_Out(); 
}

void Buzzer_Out(){
  static unsigned long prev_time = 0;
  const unsigned long interval_time = 1;
  static int buzz_cnt = 0;
  
if(speak_buzzer){
  unsigned long curr_time = millis();
  if(curr_time - prev_time >= interval_time){
    prev_time = curr_time;

    buzz_cnt++;
    if(buzz_cnt ==1000){
      buzz_cnt = 0;
      speak_buzzer = false;
    }
    else if(buzz_cnt > 0){
      tone(buzzer_pin, 2000, buzz_cnt%2);
    }
   }
  }
 }
///////////////////////////////////////////////////////////////////서보
const int servo_pin = 11;

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
