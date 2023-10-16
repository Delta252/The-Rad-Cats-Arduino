#include <Arduino.h>
#include <Servo.h>
#include "Shutter.h"




    Shutter::Shutter(int inputpin, int outputpin) :input_pin(inputpin), output_pin(outputpin) {};

    void Shutter::Initialise() {
        ShutterServo.attach(output_pin);
        ShutterServo.write(90);
        }

    void Shutter::goto_open (double desired){
        Serial.println("goto_open");
        double Input = desired+26;
        //Serial.println((unsigned int)((0.728*Input)-19.105));
        ShutterServo.write((unsigned int)((0.728*Input)-19.105));
        delay(500);
    };

    double Shutter::get(void){
        double in = 0;
        for(int i=0; i<10; i++){
            in += analogRead(input_pin);
            delay(5);
        }
        double Average = in/10;
    return ((0.4826*Average-26));
    };

    void Shutter::goto_controlled (double desired){
        uint16_t pos = ShutterServo.read();
        double diff=((desired)-(this->get()));
        //Serial.println(diff);
        double Ki = 0;
        while ((abs(diff))>3){
            // Serial.println(diff);
            double changepos= 0.3*diff;  //Kp
            // Ki += 0.0004*diff;            //Ki
            pos += (int) (changepos + Ki);
            if (pos>180) pos = 180;
            if (pos<0) pos =0;
            ShutterServo.write(pos);
            delay(150);
            diff=((desired)-(this->get()));
            Serial.println(diff);
        }
    };

    void Shutter::moveto(state pos, bool controller){
        if(controller) {
            this->goto_controlled(pos);
        }else{
            this->goto_open(pos); 
        };
    };

    void Shutter::timedExposure(state pos, unsigned long int exposure_time, bool controller){
        double return_pos = this->get();
        
        if(controller) {
            this->goto_controlled(pos);
        }else{
            this->goto_open(pos); 
        };

        delay(exposure_time);

        if(controller) {
            this->goto_controlled(return_pos);
        }else{
            this->goto_open(return_pos); 
        };
    }
