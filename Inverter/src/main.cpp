#include <Arduino.h>
#include <sine_wave.hpp>

int output_freq = 50; // 50Hz
#define carrier_freq 10 //7KHz

SPWM inverter(output_freq, carrier_freq);

#define button1 4
#define button2 6
#define led 5
long currnt,task1,task2;
bool ON = false;

// int duty = 500;
//  float p = 0.1;

void setup() {
    Serial.begin(9600);
    inverter.begin(true);
    delay(500);
    //inverter.set_amplitude(1);
    inverter.start();
    //inverter.set_amplitude(50);
    // delay(500);
    // float p=9;
    // for(int i=1; i<50; i++){
    //     inverter.set_amplitude(i);
    //     delay(100);
    // }
//  int d1 = (p*duty)/100;
// Serial.println("DUty = "+String(d1));

    pinMode(button1,INPUT);
    pinMode(button2,INPUT);
    pinMode(led,OUTPUT);

}

void loop() {
    currnt = millis();
    // if((currnt-task1) > 1000){
    //     if(ON){
    //         inverter.start();
    //         ON = !ON;
    //     }
    //     else{
    //         inverter.stop();
    //         ON = !ON;
    //     }
    //     task1 = currnt;
    // }
    if((currnt-task2)>10){
        if(digitalRead(button1)){
            delay(100);
            
            output_freq++;
            inverter.set_amplitude(output_freq);
            digitalWrite(led,!digitalRead(led));
        }
        if(digitalRead(button2)){
            delay(100);
            
            output_freq--;
            inverter.set_amplitude(output_freq);
            digitalWrite(led,!digitalRead(led));
        }
        task2 = currnt;
    }
    
    
}

