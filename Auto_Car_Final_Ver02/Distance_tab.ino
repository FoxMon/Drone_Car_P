void Distance_Setup() {
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
  } else {
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
    } else {
      if(level > 0){
        level--;
      }
    }
  }
}

//void Emergency_Car_Move(){
//  if(emergency_now){
//    emergency_now = false;
//
//    //1. @@@@
//    //2. @@@@
//  }
//}
