
#include <Arduino.h>
#include "BubbleSensor.h"


  void BubbleSensor:: setupBS() {

    //Serial.begin(9600);
    pinMode(Output, OUTPUT);        
  }


  int BubbleSensor:: Status(){
    digitalWrite(Output,HIGH);
    float sensorValue = analogRead(Input);
    float total = 0;
    for (int i=0; i<20; i++) {
      total = total + analogRead(Input);
    } 
    average = (total/20)*10;
    Serial.println(average);
     if (average > 130) {
       Serial.println("Tube present, no liquid");
       return 1;
     }
     else if (average < 125){
       Serial.println("Tube and liquid present");
       return 2;
     }
     else if (average >  125 && average < 130){
       Serial.println("No tube present");
       return 3;
     }
     else {
       return 0;
     }
    delay(500);
  };
