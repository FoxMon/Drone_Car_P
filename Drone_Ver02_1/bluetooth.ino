#include <SoftwareSerial.h>

const int blu_rx = 2; //선정리는 내가 함 걱정 ㄴ
const int blu_tx = 3;
SoftwareSerial bluetooth(blu_tx , blu_rx);
char dr_ctrl;

void Blue_Setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void Remote_Drone(){
  if(bluetooth.available()){
    dr_ctrl = bluetooth.parseInt(); // 일단 정수로 받자.

    if(dr_ctrl >= 0 && dr_ctrl <= 25){
      throttle.value = (dr_ctrl) * 10; //min 0 ~ max 250
    }
  }
}
