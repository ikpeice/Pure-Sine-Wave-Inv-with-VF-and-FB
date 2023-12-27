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
Display disp(&inv_data);



void setup() {
    Serial.begin(9600);
    // inv_data.carrier_freq = 10;
    // inv_data.output_freq = 50;
    disp.begin();

    inverter.begin(true);
    delay(50);
    //inverter.set_amplitude(1);
    //inverter.soft_start(2);
    inverter.start();
    pinMode(up_button,INPUT);
    pinMode(enter_button,INPUT);
    pinMode(down_button,INPUT);
    pinMode(led,OUTPUT);
    disp.clear();
}

void loop() {
    currnt = millis();
    if((currnt-task1) > 10){
        //lcd.clear();
        //lcd.setCursor(0,1);
        int d = analogRead(feedback_pin);
        float c = 0.09775*d;
        //lcd.print(c);
        inv_data.output_AC = c;
        inverter.set_amplitude(c);
        task1 = currnt;
    }
    if((currnt-task2)>10){
        if(get_key()==UP_KEY){
            delay(10);
            inv_data.output_freq--;
            inverter.set_amplitude(inv_data.output_freq);
            digitalWrite(led,!digitalRead(led));
        }
        if(get_key()==DOWN_KEY){
            delay(10);
            inv_data.output_freq++;
            inverter.set_amplitude(inv_data.output_freq);
            digitalWrite(led,!digitalRead(led));
        }
        if(get_key()==ENTER_KEY){
            delay(100);
            digitalWrite(led,!digitalRead(led));
            if(digitalRead(led)){
                inverter.soft_start(1);
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

