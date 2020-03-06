double Kp = 5;
double Ki = 5;
double Kd = 5;

//x
double error_x;
double error_x_per;

double des_angle_x = 10; //수정생각
double get_angle_x;

double P_x, I_x, D_x;
double PID_x;

//y
double error_y;
double error_y_per;

double des_angle_y = 10; //수정생각
double get_angle_y;

double P_y, I_y, D_y;
double PID_y;

//time = 0.004 임의임.
double T = 0.004;

void setup() {

}

void loop() {

}

void PID_x_ctrl(){
  //get_angle_x < 요거 따오는거 생각중
  error_x = des_angle_x - get_angle_x;

  P_x = Kp * error_x;
  I_x = Ki * error_x * T;
  D_x = Kd * (error_x - error_x_per) / T;

  PID_x += P_x + I_x + D_x;
  PID_x = constrain(PID_x,0,255); //PWM 0~255 < 이긴한데 수정할수도?
  //alalogWrite(?,PID_x); < 이거 하는법 잘 모르겠음

  error_x_per = error_x;
}

void PID_y_ctrl(){
  //get_angle_y < 요거 따오는거 생각중
  error_y = des_angle_y - get_angle_y;

  P_y = Kp * error_y;
  I_y = Ki * error_y * T;
  D_y = Kd * (error_y - error_y_per) / T;

  PID_y += P_y + I_y + D_y;
  PID_y = constrain(PID_y,0,255); //PWM 0~255 < 이긴한데 수정할수도?
  //alalogWrite(?,PID_y); < 이거 하는법 잘 모르겠음

  error_y_per = error_y;
  
}
