#define BUTTONS_ENABLED
//#define KEYPAD_ENABLED
#define LCD_ENABLED
//#define LED_ENABLED


#include <utilities.h>
//#include "button_keys.c"
#include <main.h>
#include <sine_wave.hpp>
//#include "display.hpp"

Inv_Data inv_data;


SPWM inverter(&inv_data);
Display disp;


void setup() {
    pinMode(13,OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(9,OUTPUT);
    digitalWrite(10,0);
    digitalWrite(9,0);
    Serial.begin(9600);
    inv_data.carrier_freq = 10;
    inv_data.output_freq = 50;
    disp.begin(&inv_data);

    inverter.begin(true);
    delay(50);
    //inverter.set_amplitude(1);
    inverter.soft_start(50);
    //inverter.start();
    pinMode(up_button,INPUT);
    pinMode(enter_button,INPUT);
    pinMode(down_button,INPUT);
    pinMode(led,OUTPUT);
    disp.clear();
}

void loop() {
    currnt = millis();
    if((currnt-task1) > 1000){
        //lcd.clear();
        //lcd.setCursor(0,1);
        
        int b = analogRead(feedback_pin);
        int c = 0.2932*b; 
        float fb = map(b,0,1023,0,100);//(c>output_target)? -1:1;
        //lcd.print(c);
        inv_data.output_AC = c;
        inv_data.batt_volt = fb;
        inverter.set_amplitude(fb);
        task1 = currnt;
    }
    if((currnt-task2)>10){
        // if(get_key()==UP_KEY){
        //     delay(300);
        //     inv_data.output_AC--;
        //     inverter.set_amplitude(inv_data.output_AC);
        //     digitalWrite(led,!digitalRead(led));
        // }
        // if(get_key()==DOWN_KEY){
        //     delay(300);
        //     inv_data.output_AC++;
        //     inverter.set_amplitude(inv_data.output_AC);
        //     digitalWrite(led,!digitalRead(led));
        // }
        if(get_key()==ENTER_KEY){
            inverter.stop();
            delay(400);
            digitalWrite(led,!digitalRead(led));
            if(digitalRead(led)){
                inverter.soft_start(50);
            }else{
                inverter.stop();
            }
            // inv_data.carrier_freq--;
            // inverter.set_carrier_freq(inv_data.carrier_freq);
            // //
            
        }
        task2 = currnt;
    }

    if((currnt-task3)>300){
        //disp.page1();
        disp.show(get_key());
        task3 = currnt;
    }
    
    
}

