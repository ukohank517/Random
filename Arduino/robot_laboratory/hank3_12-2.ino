  // arrangement plan:
  //   |-A5-A4-A3-A2-A1-A0-11-12-|
  //               ||
  //               ||
  //               ||
  //   __________________________
  //   |   [servo.front.NO.9]   |
  //   |                        |
  //   |                        |
  //   |   [servo.top.NO.10]    |
  //   |                        |
  //   |[motorL-E=6][motorR-E=5]|
  //   |[motorL-M=7][motorR-M=4]|
  //   |                        | 
  //   |[morotL--M1][motorR--M2]|
  //   |[Black->'-'][Red->'+']  |
  



//information of line race
//name     : bef->aft
//target E : 65 -> 55
//target F : 60 -> 50
//target A : 65 -----
//target B :125 -----
//target C : 68 -----
//target D :123 -----


#include<Servo.h>
Servo front;
Servo top;
int ER=5;
int MR=4;
int EL=6;
int ML=7;

  //about motor:
  //  digitalWrite ML/MR,HIGH->正転 LOW->逆転
  //ex.)
  //digitalWrite(ML,HIGH);
  //digitalWrite(MR,HIGH);
  
  
  //  digitalWrite EL/ER,vallut->speed
   //ex.)
  //analogWrite(EL,value);
  //analogWrite(ER,value);
const byte PIN_ROT=2;
unsigned long counter=0;
unsigned long one_round=17300;
int sensorLLLL=A5;
int sensorLLL=A4;
int sensorLL=A3;
int sensorL=A2;
int sensorR=A1;
int sensorRR=A0;
int sensorRRR=11;
int sensorRRRR=12;
int hosei=0;
   //about sensor:
  //  the light will shine when it read white
  //  white line->0
  //  black field->1
  
  
  void cont(){
    counter++;
  }
     
void setup(){  
  Serial.begin(9600);
  pinMode(ML,OUTPUT);
  pinMode(MR,OUTPUT);
  //pinMode(EL,OUTPUT);
  //pinMode(ER,OUTPUT);
  pinMode(PIN_ROT,INPUT);
  front.attach(10);
  front.write(87);
  top.attach(9);
  top.write(90);
  delay(6000);
} 

void loop(){   
  
  counter%=one_round;
  
  attachInterrupt(digitalRead(PIN_ROT),cont,FALLING);
  
  digitalWrite(ML,HIGH);
  digitalWrite(MR,HIGH);
  
  

 // normall();   
  int situation=0b0000000;
  if(!digitalRead(sensorLLLL))situation+=0b1000000;
  if(!digitalRead(sensorLLL))situation+=0b0100000;
  if(!digitalRead(sensorLL))situation+=0b0010000;
  if(!digitalRead(sensorL))situation+=0b0001000;
  if(!digitalRead(sensorR))situation+=0b0000100;
  if(!digitalRead(sensorRR))situation+=0b0000010;
   if(!digitalRead(sensorRRR))situation+=0b0000001;
  
  
  switch(situation){
    case(0b1000000):
      analogWrite(EL,102);
      analogWrite(ER,123);
      front.write(69);
      break;

    case(0b1100000):
      analogWrite(EL,105);
      analogWrite(ER,123);
      front.write(72);
      break;

    case(0b0100000):
      analogWrite(EL,108);
      analogWrite(ER,123);
      front.write(74);
      break;

    case(0b0110000):
    if(hosei>=3)
    {
      analogWrite(EL,111);
      analogWrite(ER,123);
      front.write(86);
      delay(200);
      analogWrite(EL,123);
      analogWrite(ER,123);
      front.write(90);
      delay(2000);
      analogWrite(EL,0);
      analogWrite(ER,0);
      delay(12000);

    }

    else{
      analogWrite(EL,111);
      analogWrite(ER,123);
      front.write(77);
    }
       break;

    case(0b0010000):
      analogWrite(EL,114);
      analogWrite(ER,123);
      front.write(79);
      break;

    case(0b0011000):
      analogWrite(EL,117);
      analogWrite(ER,123);
       front.write(82);
      break;

    case(0b0001000):
      analogWrite(EL,120);
      analogWrite(ER,123);
      front.write(84);
      break;
    case(0b0001100):
      analogWrite(EL,123);
      analogWrite(ER,123);
      front.write(87);
      break;
    case(0b0000100):
      analogWrite(EL,123);
      analogWrite(ER,120);
      front.write(90);
      break;

    case(0b0000110):
       analogWrite(EL,123);
      analogWrite(ER,117);
      front.write(92);
      break;

    case(0b0000010):
      analogWrite(EL,123);
      analogWrite(ER,114);
      front.write(95);
      break;

    case(0b0000011):
      analogWrite(EL,123);
      analogWrite(ER,111);
      front.write(97);
      break;

    case(0b0000001):
      analogWrite(EL,123);
      analogWrite(ER,108);
      front.write(100);
       break;

      
    case(0b00000000):
      analogWrite(EL,0);
      analogWrite(ER,0);
      break;
    }
    
   
    
  if(0<=counter&&counter<=2090)top.write(90);
  if(2090<=counter&&counter<=2240)top.write(40);//OK
  if(2210<counter&&counter<=3710)top.write(90);
  if(3710<counter&&counter<=3910)top.write(40);//
  if(3910<counter&&counter<=8300)top.write(90);
  if(8300<counter&&counter<=10000)top.write(65);//OK
  if(10000<counter&&counter<=11990)top.write(116);
  if(11990<counter&&counter<=13200)top.write(65);
  if(13200<counter&&counter<=16000)top.write(116);
  if(16000<counter)top.write(90);


if(counter == 1500) hosei++;    
Serial.print(counter);
Serial.println(hosei);

}

