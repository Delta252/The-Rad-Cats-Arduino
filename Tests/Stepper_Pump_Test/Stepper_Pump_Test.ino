
// CNC Shield Stepper  Control Demo
// Superb Tech
// www.youtube.com/superbtech
#include <Servo.h>
#include "AccelStepper.h"

#define pinSer 12
//Motor interface type: 1 = Stepper driver
#define MOTOR_INTERFACE_TYPE 1
//Only change step, dir, or enable if the PCB changes the GPIO pins available to these 
#define STEP 8
#define DIR 7
#define ENABLE 4
#define INPUT 0
#define OUTPUT 80
#define ANGLE_MIDDLE 40

#define maxStep 1000

Servo pumpValve;
AccelStepper accelMotor(MOTOR_INTERFACE_TYPE, STEP, DIR);
float a = 0;
String step;

void setup() {
  Serial.begin(115200);
  pumpValve.attach(pinSer);
  pumpValve.write(ANGLE_MIDDLE);
  delay(500);
  // pumpValve.write(INPUT); 
  // delay(500);
  // pumpValve.write(ANGLE_MIDDLE); 

  //Initialise parameters regarding speed
  accelMotor.setMaxSpeed(60);
  accelMotor.setSpeed(60);
  accelMotor.setAcceleration(20);
}

void loop() {
  if(Serial.available()>0){
    step = Serial.readStringUntil(' ');
    Serial.println("Step: " + (String)step);
    move(step.toInt());
  }
  Serial.flush();
 
  // accelMotor.moveTo(-2000);

  // while(accelMotor.distanceToGo() != 0)
  // {
  //   accelMotor.run();
  // }
}

void move(int stepToMove)
{
  //Set the desired step
  Serial.println("Distance to move:" + (String)stepToMove);
  pumpValve.write(INPUT);
  delay(500);
  accelMotor.moveTo(stepToMove);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }

  //Set the desired step
  pumpValve.write(OUTPUT);
  delay(500);
  Serial.println("New Speed: "+ (String)accelMotor.speed());
  accelMotor.moveTo(0);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }
}