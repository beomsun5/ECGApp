#include <SoftwareSerial.h>

int Tx = 6; //전송 보내는핀  
int Rx = 7; //수신 받는핀
int count = 512; //테스트 횟수
SoftwareSerial bluetooth(Tx,Rx);
String A;
int tmp1, tmp2;
byte ecg_data[1024];




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);
  //Serial.print("tmp,tmp2");
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = bluetooth.read();
  if(a!=-1) {
    Serial.println(a);  
    count = 0;  
  }
  if(count<512) {
    if (bluetooth.available()) {
      Serial.write(bluetooth.read());
    }
    if (Serial.available()) {
      bluetooth.write(Serial.read());
    }
    /*
    for(int i=0; i<1024; i++) {
      cyh[i] = i%256;
    }
    bluetooth.write(cyh,1024);
    */
    tmp2 = analogRead(A0);
    tmp1 = (tmp2 & 0xff00);
    tmp2 = (tmp2 & 0x00ff);
    ecg_data[count*2] = (tmp1>>8)+1;
    ecg_data[count*2+1] = tmp2+1;
    
    Serial.print(tmp1);
    Serial.print(" + ");
    Serial.println(tmp2);


    
    delay(20);
    count++;
  
  }
  else if(count == 512){
    bluetooth.write(ecg_data,1024);
    count++;
  }
    //
    //bluetooth.print("567");
    //delay(1000);
    

/*
    if(digitalRead(10) == 1 || digitalRead(11) == 1) {
    
      Serial.print('!');
    }
    else {
      Serial.println(analogRead(A0));   
      delay(20);  
    }
  */
}
