#include <SoftwareSerial.h>      // 직렬통신을 위한 라이브러리 포함

#define A 0x04 //키보드 키값 define
#define B 0x05
#define X 0x1b
#define Y 0x1c

const byte rxPin=2;    // rx 핀을2번으로 지정
const byte txPin=3;    // tx 핀을3번으로 지정
 
SoftwareSerial BTSerial(rxPin,txPin);   //블루투스 시리얼 핀 설정

int Button4 = 13,Button3 = 12,Button2 = 11,Button1 = 10;  //버튼 핀 설정
unsigned char key[12] = { 0x0c, 0x00, 0xa1, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; //블루투스 모듈이 받을수 있는 패킷 형식

void setup() {
  pinMode(Button4, INPUT);                 // 버튼4 핀을 입력으로 설정
  pinMode(Button3, INPUT);                 // 버튼3 핀을 입력으로 설정
  pinMode(Button2, INPUT);                 // 버튼2 핀을 입력으로 설정
  pinMode(Button1, INPUT);                 // 버튼1 핀을 입력으로 설정
  
  Serial.begin(9600);                    // 9600 속도로 시리얼 통신 시작
  BTSerial.begin(115200);         // 블루투스 통신 속도를 115200으로 설정
}

void loop() {
  int sensorVal4 = digitalRead(Button4);  //각 버튼의 
  int sensorVal3 = digitalRead(Button3);  //디지털 값을 
  int sensorVal2 = digitalRead(Button2);  //sensorVal에 
  int sensorVal1 = digitalRead(Button1);  //저장  
  
  if (sensorVal4 == LOW) //버튼이 눌렸을 때
  { 
    key[6] = Y; //키값  
    if(sensorVal1 == LOW)//버튼이 동시에 눌렸을 때(2개까지만)
    {
      key[7] = A;            
    }
    else if(sensorVal2 == LOW)
    {
      key[7] = B;
    }
    else if(sensorVal3 == LOW)
    {
      key[7] = X;
    }
    BTSerial.write(key,12);
    Serial.write(key,12);
  }

  else if (sensorVal3 == LOW ) 
  {         
    key[6] = X; //키값   
    if(sensorVal1 == LOW)//버튼이 동시에 눌렸을 때(2개까지만)
    {
      key[7] = A;            
    }
    else if(sensorVal2 == LOW)
    {
      key[7] = B;
    }
    else if(sensorVal4 == LOW)
    {
      key[7] = Y;
    }            
    BTSerial.write(key,12);
    Serial.write(key,12);
  }
 
  else if (sensorVal2 == LOW) 
  {       
    key[6] = B; //키값 
    if(sensorVal1 == LOW)//버튼이 동시에 눌렸을 때(2개까지만)
    {
      key[7] = A;            
    }
    else if(sensorVal4 == LOW)
    {
      key[7] = Y;
    }
    else if(sensorVal3 == LOW)
    {
      key[7] = X;
    }              
    BTSerial.write(key,12);
    Serial.write(key,12);
  }
  
  else if (sensorVal1 == LOW) 
  {       
    key[6] = A; //키값     
    if(sensorVal4 == LOW)//버튼이 동시에 눌렸을 때(2개까지만)
    {
      key[7] = Y;            
    }
    else if(sensorVal2 == LOW)
    {
      key[7] = B;
    }
    else if(sensorVal3 == LOW)
    {
      key[7] = X;
    }          
    BTSerial.write(key,12);
    Serial.write(key,12);
  }

  else  //release
  {
    key[6] = 0x00; //버튼 뗌
    key[7] = 0x00;
    BTSerial.write(key,12);
    Serial.write(key,12);
  }
  
  delay(10); //채터링 방지

}
