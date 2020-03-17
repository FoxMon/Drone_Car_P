void Led_Set_Up(void) { // Initial Led Set_Up
  // Left, Right LED Output
  pinMode(front_left_led, OUTPUT); 
  pinMode(front_right_led, OUTPUT);
  pinMode(rear_left_led, OUTPUT);
  pinMode(rear_right_led, OUTPUT);
  pinMode(A2, INPUT);
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
  Bright_Sensor_Loop();
  Auto_Control_Led();
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
  Read_Bright_Value();
}

void Read_Bright_Value(void) { // Read CDS Sensor
  const unsigned long duration_millis = 350; // Blink Time Interval
  static unsigned long previous_millis = 0; // Previous TIme
  unsigned long cur_time = millis(); // Current Time

  if((cur_time - previous_millis) >= duration_millis) {
    previous_millis = cur_time;

    bright_value = analogRead(A2); // Read CDS Sensor Value
    bright_flag = true;
  }
}

void Auto_Control_Led(void) { // Check CDS and Control LEDs
  if(bright_flag) {
    bright_flag = false;

    if(initial_bright == ALLLEDOFF) { // Turn on LED
      if(bright_value >= LIMIT){
        initial_bright = ALLLEDON;
        change_led = ALLLEDON;
        change_led_on_off = true;
        bright_flag = true;
      }
    } else if(initial_bright == ALLLEDON) { // Turn off LED
      if(bright_value <= BRIGHT) {
        initial_bright = ALLLEDOFF;
        change_led = ALLLEDOFF;
        change_led_on_off = true;
        bright_flag = true;
      }
    }
  }
}
