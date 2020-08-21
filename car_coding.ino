#define left_wheel_back 4
#define left_wheel_go 5
#define right_wheel_back 6
#define right_wheel_go 7
#define echoPin  8
#define trigPin  9
#define front_led 11
#define rear_led 12


String remote_read = "";
String run_drive = "";
String change_led = "";
String blink_led = "";
const long limit_distance = 15.0; //cm
unsigned long previous_millis = 0;
const long interval = 500;
int blink_led_state = LOW;
long cm;
int distance_level = 0;

bool auto_drive_check = false;
bool control_change = false;
bool change_drive_action = false;
bool change_led_action = false;
bool blink_led_action = false;
bool blink_led_control = false;
bool distance_change_check = false;
bool emergency_check = false;


void setup() {
  Serial.begin(9600);
  Motor_setup();
  Ultra_Sonic_setup();
  Led_setup();
}

void loop() {
  Remote_Control_loop();
  Drive_loop();
  Led_loop();
  Distance_loop();
}

String readSerial()   {
  String str = "";
  char ch;

  while ( Serial.available() > 0 )    {
    ch = Serial.read();
    str.concat(ch);
    delay(10);
  }
  return str;
}

void Remote_Control_loop(void) {
  Remote_User_Input();
  Check_User_Input();
}
void Drive_loop(void) {
  Auto_Drive_Action();
  Remote_Drive_Action();
}
void Led_loop(void) {
  Remote_Led_Action();
  Blink_Led_Action();
}

void Remote_User_Input(void) {
  String input = "";
  input = readSerial();
  if (input == "AUTODRIVE") {
    auto_drive_check = true;    //go -> Auto_Drive_Action()
  }
  if (input != remote_read) {
    remote_read = input;
    control_change = true;
  }
}

void Check_User_Input(void) {
  if (control_change) {

    control_change = false;

    if (remote_read == "GO" ||
        remote_read == "BACK" ||
        remote_read == "LEFT" ||
        remote_read == "RIGHT" ||
        remote_read == "STOP") {
      run_drive = remote_read;
      change_drive_action = true; //go -> Remote_Drive_Action()
    }
    else if (remote_read == "FRONTLEDON" ||
             remote_read == "FRONTLEDOFF" ||
             remote_read == "REARLEDON"  ||
             remote_read == "REARLEDOFF" ||
             remote_read == "ALLLEDON" ||
             remote_read == "ALLLEDOFF") {
      change_led = remote_read;
      change_led_action = true; //go -> Remote_Led_Action()
    }
    else if (remote_read == "REARLEFTBLINK" ||
             remote_read == "REARRIGHTBLINK" ||
             remote_read == "ALLLEDBLINK") {
      blink_led = remote_read;
      blink_led_action = true;  //go -> Blink_Led_Action()
    }
  }
}
void Auto_Drive_Action(void) {
  if (auto_drive_check) {
    auto_drive_check = false;
  }
}
void Remote_Drive_Action(void) {
  if (change_drive_action) {
    change_drive_action = false;

    if (run_drive == "GO") {
      Go_Forward();
    }
    else if (run_drive == "BACK") {
      Go_Backward();
    }
    else if (run_drive == "LEFT") {
      Trun_Left();
    }
    else if (run_drive == "RIGHT") {
      Trun_Right();
    }
    else if (run_drive == "STOP") {
      Stop_Drive();
    }
  }
}

void Remote_Led_Action(void) {
  if (change_led_action) {
    change_led_action = false;

    if (change_led == "FRONTLEDON") {
      Front_Led_on();
    }
    else if (change_led == "FRONTLEDOFF") {
      Front_Led_off();
    }
    else if (change_led == "REARLEDON") {
      Rear_Led_on();
    }
    else if (change_led == "REARLEDOFF") {
      Rear_Led_off();
    }
    else if (change_led == "ALLLEDON") {
      All_Led_on();
    }
    else if (change_led == "ALLLEDOFF") {
      All_Led_off();
    }
  }
}

void Blink_Led_Action(void) {
  if (blink_led_action) {
    blink_led_action = false;

    if (blink_led == "REARLEFTBLINK") {
      Rear_Left_Blink();
    }
    else if (blink_led == "REARRIGHTBLINK") {
      Rear_Right_Blink();
    }
    else if (blink_led == "ALLLEDBLINK") {
      blink_led_control = true;
      Blink_Led();
    }
  }
}

void Go_Forward(void) {
  digitalWrite(left_wheel_go, HIGH);
  digitalWrite(right_wheel_go, HIGH);
}
void Go_Backward(void) {
  digitalWrite(left_wheel_back, HIGH);
  digitalWrite(right_wheel_back, HIGH);
}
void Trun_Left(void) {
  digitalWrite(left_wheel_back, HIGH);
  digitalWrite(right_wheel_go, HIGH);
}
void Trun_Right(void) {
  digitalWrite(right_wheel_back, HIGH);
  digitalWrite(left_wheel_go, HIGH);
}
void Stop_Drive(void) {
  digitalWrite(left_wheel_back, LOW);
  digitalWrite(left_wheel_go, LOW);
  digitalWrite(right_wheel_back, LOW);
  digitalWrite(right_wheel_go, LOW);
}

void Motor_setup(void) {
  pinMode(left_wheel_back, OUTPUT);   //L BACK
  pinMode(left_wheel_go, OUTPUT);   //L GO
  pinMode(right_wheel_back, OUTPUT);   //R BACK
  pinMode(right_wheel_go, OUTPUT);   //R GO

  digitalWrite(left_wheel_back, LOW);
  digitalWrite(left_wheel_go, LOW);
  digitalWrite(right_wheel_back, LOW);
  digitalWrite(right_wheel_go, LOW);
}

void Ultra_Sonic_setup(void) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void Led_setup(void) {
  pinMode(front_led, OUTPUT);
  pinMode(rear_led, OUTPUT);

  digitalWrite(front_led, LOW);
  digitalWrite(rear_led, LOW);
}


void Front_Led_on(void) {
  digitalWrite(front_led, HIGH);
}
void Front_Led_off(void) {
  digitalWrite(front_led, LOW);
}
void Rear_Led_on(void) {
  digitalWrite(rear_led, HIGH);
}
void Rear_Led_off(void) {
  digitalWrite(rear_led, LOW);
}

void All_Led_on(void) {
  Front_Led_on();
  Rear_Led_on();
}
void All_Led_off(void) {
  Front_Led_off();
  Rear_Led_off();
}


//void Blink_Led(void) {
//  const unsigned long duration_millis = 350;
//  static unsigned long previous_millis = 0;
//  static int count_blink = 0;
//
//  if (blink_led_control) {
//    unsigned long cur_time = millis();
//
//    if ((cur_time - previous_millis) >= duration_millis) {
//      previous_millis = cur_time;
//      count_blink++;
//      Serial.println(count_blink);
//
//      if (count_blink == 10) {
//        count_blink = 0;
//        blink_led_control = false;
//        change_led_action = true;
//        Serial.println(blink_led_control);
//      }
//      else {
//        digitalWrite(front_led, count_blink % 2);
//        digitalWrite(rear_led, count_blink % 2);
//      }
//    }
//  }
//}
void Blink_Led(void) {
  unsigned long current_millis = millis();

  if (current_millis - previous_millis >= interval) {
    previous_millis = current_millis;

    if (blink_led_state == LOW) {
      blink_led_state = HIGH;
    }
    else {
      blink_led_state = LOW;
    }
    digitalWrite(front_led, blink_led_state);
    digitalWrite(rear_led, blink_led_state);
  }

}

void Rear_Left_Blink(void) {
  Serial.println("not use");

}
void Rear_Right_Blink(void) {
  Serial.println("not use");
}


long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
void Distance_loop(void){
  Ultra_Sonic_Action();
  Emergency_Check();
}

void Ultra_Sonic_Action(void) {
  long duration,previous_distance = 0.0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.println(" cm");
  delay(100);
  if (cm != previous_distance) {
    previous_distance = cm;
    distance_change_check = true;
  }
}

void Emergency_Check(void) {

  if (distance_change_check) {
    distance_change_check = false;
    
   
    if (cm <= limit_distance) {
      distance_level++;
     

      if (distance_level == 10) {
        distance_level = 0;
        emergency_check = true;
      }
    }
  }
}

void Emergency_Action(void){
  if(emergency_check){
    Stop_Drive();
    Blink_Led();
  }
}
