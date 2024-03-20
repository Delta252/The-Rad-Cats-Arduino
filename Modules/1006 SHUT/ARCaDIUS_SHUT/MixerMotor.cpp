#include <Arduino.h>
#include "MixerMotor.h"
 
void MixerMotor:: SetUpMotor() {
  pinMode(E,OUTPUT);
  pinMode(MP1,OUTPUT);
  pinMode(MP2,OUTPUT);
  analogWrite(E,0);
}  

void MixerMotor:: StopMotor(){
  //digitalWrite(E,LOW); //slow stop
  digitalWrite(MP1,LOW); //one way
  digitalWrite(MP2,LOW);
}
 
void MixerMotor:: SetSpeed(int PWM) {
  analogWrite(E,PWM);
  delay(500);
  digitalWrite(MP1,HIGH); //one way
  digitalWrite(MP2,LOW);
  // delay(500);
  // analogWrite(E,PWM);
}
