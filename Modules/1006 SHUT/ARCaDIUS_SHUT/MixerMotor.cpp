#include <Arduino.h>
#include "MixerMotor.h"
 
void MixerMotor:: SetUpMotor() {
  pinMode(E,OUTPUT);
  pinMode(MP1,OUTPUT);
  pinMode(MP2,OUTPUT);
}  

void MixerMotor:: StopMotor(){
  digitalWrite(E,LOW); //slow stop
}
 
void MixerMotor:: SetSpeed(int PWM) {
  analogWrite(E,100);
  digitalWrite(MP1,HIGH); //one way
  digitalWrite(MP2,LOW);
  delay(500);
  analogWrite(E,PWM); 
  digitalWrite(MP1,HIGH); //one way
  digitalWrite(MP2,LOW);
}
