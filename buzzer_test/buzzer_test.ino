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
  const long interval_time = 1;
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

void setup(){
  Buzzer_Setup();
}
void loop(){
  Buzzer_Loop();
}
