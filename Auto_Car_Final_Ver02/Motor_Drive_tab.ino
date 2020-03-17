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
