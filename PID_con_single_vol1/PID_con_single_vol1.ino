//PID, single angle 

//게인값, 현재 임의
double Kp = 1.5;
double Ki = 2.5;
double Kd = 3.0;

double error;
double error_per;

double goal_angle = 10; //원하는 각 임의
double get_angle;

double p_con, i_con, d_con;
double T = 0.004; //임의
double pid_con;


void setup() {

}

void loop() {
  pid_control;

}

void pid_control(){
  get_angle
  error = goal_angle - get_angle;

  p_con = Kp * error;
  i_con = Ki * error * T;
  d_con = Kd * (error - error_per) / T;

  pid_con = p_con + i_con + d_con;
  pid_con = constrain(pid_con,0,255); //PWM 0~255
  //analogWrite(?,pid_con)

  error_per = error;
}
