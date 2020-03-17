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
