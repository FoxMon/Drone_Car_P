// Drone_Rc_Car_Test
// 2020-03-12
// LED_Ver_01
// Remote_Control_Ver_01
// Motor_Control_Ver_01

#define LIMIT 200
#define BRIGHT 800

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

void Led_Set_Up(void) { // Initial Led Set_Up
  // Left, Right LED Output
  pinMode(front_left_led, OUTPUT); 
  pinMode(front_right_led, OUTPUT);
  pinMode(rear_left_led, OUTPUT);
  pinMode(rear_right_led, OUTPUT);

  // Left, Right LED Off
  digitalWrite(front_left_led, LOW);
  digitalWrite(front_right_led, LOW);
  digitalWrite(rear_left_led, LOW);
  digitalWrite(rear_right_led, LOW);
}

void Led_Loop(void) { // Loop Led Controll
  Run_Led_On_Off();
  Run_Led_Blink();
  Control_Rear_Left_Blink();
  Control_Rear_Right_Blink();
}

void Run_Led_On_Off(void) { // Change Led On / Off
  if(change_led_on_off) { // True? or False?
    change_led_on_off = false; 

    if(change_led == FRONTLEDON) { // UserInput -> Q
      Front_Light_On(); // front on
    } else if(change_led == FRONTLEDOFF) { // UserInput -> q
      Front_Light_Off(); // front off
    } else if(change_led == REARLEDON) { // UserInput -> W
      Rear_Light_On(); // rear on
    } else if(change_led == REARLEDOFF) { // UserInput -> w
      Rear_Light_Off(); // rear off
    } else if(change_led == ALLLEDON) { // UserInput -> E
      All_Light_On(); // all of leds on
    } else if(change_led == ALLLEDOFF) { // UserInput -> e
      All_Light_Off(); // all of leds off
    }
  }
}

void Run_Led_Blink(void) { // Control Blink Flag
  if(blink_led_on_off) { // True? or False?
    blink_led_on_off = false;

    if(blink_led == REARLEFTBLINK) { // UserInput -> 'R'
      rear_left_blink = true;
      rear_right_blink = false;
    } else if(blink_led == REARRIGHTBLINK) { // UserInput -> 'r'
      rear_left_blink = false;
      rear_right_blink = true;
    }
  }
}

void Control_Rear_Left_Blink(void) { // Control Rear Left Led Blink
  const unsigned long duration_millis = 350; // Blink Time Interval
  static unsigned long previous_millis = 0; // Previous TIme
  static int count_blink = 0; // Counting variable

  if(rear_left_blink) { 
    unsigned long cur_time = millis();
    
    if((cur_time - previous_millis) >= duration_millis) {
      previous_millis = cur_time;
      count_blink++;

      if(count_blink == 10) {
        count_blink = 0;  
        rear_left_blink = false;
        change_led_on_off = true;
      } else {
          digitalWrite(rear_left_led, count_blink%2);
      }
    }
  }
}

void Control_Rear_Right_Blink(void) { // Control Rear Right Led Blink
  const unsigned long duration_millis = 350; // Blink Time Interval
  static unsigned long previous_millis = 0; // Previous TIme
  static int count_blink = 0; // Counting variable

  if(rear_right_blink) {
    unsigned long cur_time = millis();

    if((cur_time - previous_millis) >= duration_millis) {
      previous_millis = cur_time;
      count_blink++;

      if(count_blink == 10) {
        count_blink = 0;  
        rear_right_blink = false;
        change_led_on_off = true;
      }     else {
         digitalWrite(rear_right_led, count_blink%2);
      }
    }
  }
}

void Front_Light_On(void) { // Turn on Front LED
  digitalWrite(front_left_led, HIGH);
  digitalWrite(front_right_led, HIGH);
}

void Front_Light_Off(void) { // Turn off Front LED
  digitalWrite(front_left_led, LOW);
  digitalWrite(front_right_led, LOW);
}

void Rear_Light_On(void) { // Turn On Rear LED
  digitalWrite(rear_left_led, HIGH);
  digitalWrite(rear_right_led, HIGH);
}

void Rear_Light_Off(void) { // Turn Off Rear LED
  digitalWrite(rear_left_led, LOW);
  digitalWrite(rear_right_led, LOW);
}

void All_Light_On(void) { // Turn on All of LEDs
  Front_Light_On();
  Rear_Light_On();
}

void All_Light_Off(void) { // Turn off All of LEDs
  Front_Light_Off();
  Rear_Light_Off();
}

void Bright_Sensor_Loop() { // CDS Sensor
  Read_Bright_Value(); // Read CDS
}

void Read_Bright_Value(void) { // Read CDS Sensor
  const unsigned long duration_millis = 350; // Blink Time Interval
  static unsigned long previous_millis = 0; // Previous TIme
  unsigned long cur_time = millis(); // Current Time

  if((cur_time - previous_millis) >= duration_millis) {
    previous_millis = cur_time;

    bright_value = analogRead(10); // Read CDS Sensor Value
    bright_flag = true;
  }
}

void Auto_Control_Led(void) { // Check CDS and Control LEDs
  if(bright_flag) {
    bright_flag = false;

    if(initial_bright == ALLLEDOFF) { // Turn on LED
      if(bright_value <= LIMIT){
        initial_bright = ALLLEDON;
        change_led = ALLLEDON;
        bright_flag = true;
      }
    } else if(initial_bright == ALLLEDON) { // Turn off LED
      if(bright_value >= BRIGHT) {
        initial_bright = ALLLEDOFF;
        change_led = ALLLEDOFF;
        bright_flag = false;
      }
    }
  }
}

void Remote_Control_Set(void) { // Set Remote Control ( Serial )
  Serial.begin(9600); // Serial Speed
}

void Remote_Control_Loop(void) { // Loopin
 Remote_User_input(); 
 Check_Remote_Input();
}

void Remote_User_input(void) { // Check User Input
  if(Serial.available()) {
    char input = Serial.read();
  
    if(input == AUTODRIVE) {
      auto_drive_check =  true;
    }

 
    // if emergency state ??

    if(input != remote_read) {
      remote_read = input;    
      control_change = true;
      //blink_led_on_off = true;   
    }
  }
}

void Check_Remote_Input(void) { // Check Remote Control
  if(control_change) {
    control_change = false;

     // Big -> Small
     
    if(remote_read == GO_B ||
    remote_read == BACK_B ||
    remote_read == LEFT_B ||
    remote_read == RIGHT_B ||
    remote_read == STOP_B ||
    remote_read == GOANDLEFT_B ||
    remote_read == GOANDRIGHT_B ||
    remote_read == BACKANDLEFT_B ||
    remote_read == BACKANDRIGHT_B )
    {
      remote_read = (remote_read - 'A') + 'a';
    }
    if(remote_read == GO ||
    remote_read == BACK ||
    remote_read == LEFT ||
    remote_read == RIGHT ||
    remote_read == STOP ||
    remote_read == GOANDLEFT ||
    remote_read == GOANDRIGHT ||
    remote_read == BACKANDLEFT ||
    remote_read == BACKANDRIGHT  ){
      run_drive = remote_read;
      change_drive_action = true;
    } 
    else if(remote_read == SPEED0 ||
    remote_read == SPEED1 ||
    remote_read == SPEED2 ||
    remote_read == SPEED3) {
      drive_speed = remote_read;
      change_drive_speed = true;
    } 
    else if(remote_read == FRONTLEDON || 
    remote_read == FRONTLEDOFF ||
    remote_read == REARLEDON ||
    remote_read == REARLEDOFF ||
    remote_read == ALLLEDON ||
    remote_read == ALLLEDOFF) {
      change_led = remote_read;
      change_led_on_off = true;
    } 
    else if(remote_read == REARLEFTBLINK ||
    remote_read == REARRIGHTBLINK) {
      blink_led = remote_read;
      blink_led_on_off = true;
    } // add Horn
  }
}

void Motor_SetUp(void) { // Motor SetUp
  pinMode(dirA, OUTPUT);

  digitalWrite(dirA, LOW);
  analogWrite(pwmA, 0);

  pinMode(dirB, OUTPUT);
  
  digitalWrite(dirB, LOW);
  analogWrite(pwmB, 0);
}

void Motor_Loop(void) { // Motor Loop
  Check_Drive_Action();
  Check_Drive_Speed();
}

void Check_Drive_Action(void) { // Check Drive Mode
  if(change_drive_action) {
    change_drive_action = false;

    if(run_drive == GO) {
      Go_Forward();
    } else if(run_drive == BACK) {
      Go_Backward();
    } else if(run_drive == LEFT) {
      Turn_Left();
    } else if(run_drive == RIGHT) {
      Turn_Right();
    } else if(run_drive == STOP) {
      Stop_Drive();
    } else if(run_drive == GOANDLEFT) {
      Turn_Left();
      
      blink_led = REARLEFTBLINK;
      blink_led_on_off = true;
    } else if(run_drive == GOANDRIGHT) {
      Turn_Right();

      blink_led = REARRIGHTBLINK;
      blink_led_on_off = true;
    } else if(run_drive == BACKANDLEFT) {
      Turn_Right();
    } else if(run_drive == BACKANDRIGHT) {
      Turn_Left();
    }
  }
}

void Go_Forward(void) { // GO
  // extern unsigned int accel;

  digitalWrite(dirA, HIGH);
//  analogWrite(pwmA, 200 + accel);
  analogWrite(pwmA, 200);
  digitalWrite(dirB, HIGH);
//  analogWrite(pwmB, 200 + accel);
  analogWrite(pwmB, 200);
}

void Go_Backward(void) { // Back
  digitalWrite(dirA, LOW);
  analogWrite(pwmA, 200);
  digitalWrite(dirB, LOW);
  analogWrite(pwmB, 200);
}

void Turn_Left(void) { // Left
  digitalWrite(dirA, LOW);
  analogWrite(pwmA, 200);
   digitalWrite(dirB, HIGH);
  analogWrite(pwmB, 200);
}

void Turn_Right(void) { // Right
  digitalWrite(dirA, HIGH);
  analogWrite(pwmA, 200);
  digitalWrite(dirB, LOW);
  analogWrite(pwmB, 200);
}

void Stop_Drive(void) { // Stop
   digitalWrite(dirA, LOW);
   analogWrite(pwmA, 0);
   digitalWrite(dirB, LOW);
   analogWrite(pwmB, 0);

  // extern unsigned inr accel;
  // accel = 0;
}

void Check_Drive_Speed(void) { // Check Drive Speed Order
  if(change_drive_speed) {
    change_drive_speed = false;

    Control_Drive_Speed();
  }
}

void Control_Drive_Speed(void) { // Contrl Drive Speed
  int car_speed = drive_speed;

  if(car_speed != SPEED3) {
    car_speed -= SPEED0;
  } else {
    car_speed = 10;
  }

  // accel = car_speed * (50/10.0);

  change_drive_speed = true;
}

void setup(void) {
  Motor_SetUp();
  Remote_Control_Set();
  Led_Set_Up();
}

void loop(void) {
  Motor_Loop();
  Remote_Control_Loop();
  Led_Loop();
}
