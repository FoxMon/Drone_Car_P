#include <PinChangeInterrupt.h>

const int trig = 8;
const int echo = 9;

void Distrance_Setup() {
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);

attachPCINT(digitalPinToPCINT(echo), EchoIsr, CHANGE);
}

unsigned long distance = 50;
bool fucking_distance = false;

void EchoIsr (void){
  static volatile unsigned long start_echo = 0;
  static volatile unsigned long end_echo = 0;

  unsigned int echo_pin_on = digitalRead(echo);

  if(echo_pin_on == HIGH){
    start_echo = micros();
  }
  else(
    end_echo = micros();
    unsigned long duration = end_echo - start_echo;
    distance = duration / 58;
    fucking_distance = true;
  }
}

bool emergency_now = false;
const int what_thing = 15; //cm

void Distance_Checking(){
  
  if(fucking_distance){
    fucking_distance = false;

    static int level = 0;
    if(level <= what_thing){
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

void Emergency_Loop(){
  if(emergency_now)
}

 
  
