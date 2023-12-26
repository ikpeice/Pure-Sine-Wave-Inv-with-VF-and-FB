#define BUTTONS_ENABLED
//#define KEYPAD_ENABLED
#define LCD_ENABLED
//#define LED_ENABLED

#include <main.h>
#include <utilities.h>
#include <sine_wave.hpp>




SPWM inverter(output_freq, carrier_freq);
Display disp;





void setup() {
    Serial.begin(9600);
    disp.start();

    inverter.begin(true);
    delay(50);
    //inverter.set_amplitude(1);
    inverter.soft_start(2);
    pinMode(up_button,INPUT);
    pinMode(enter_button,INPUT);
    pinMode(down_button,INPUT);
    pinMode(led,OUTPUT);
}

void loop() {
    currnt = millis();
    if((currnt-task1) > 10){
        //lcd.clear();
        //lcd.setCursor(0,1);
        int d = analogRead(feedback_pin);
        float c = 0.09775*d;
        //lcd.print(c);
        inverter.set_amplitude(c);
        task1 = currnt;
    }
    if((currnt-task2)>10){
        if(get_key()==UP_KEY){
            delay(10);
            output_freq--;
            inverter.set_amplitude(output_freq);
            digitalWrite(led,!digitalRead(led));
        }
        if(get_key()==DOWN_KEY){
            delay(10);
            output_freq++;
            inverter.set_amplitude(output_freq);
            digitalWrite(led,!digitalRead(led));
        }
        if(get_key()==ENTER_KEY){
            delay(100);
            //inverter.stop();
            carrier_freq--;
            inverter.set_carrier_freq(carrier_freq);
            //inverter.start();
            digitalWrite(led,!digitalRead(led));
        }
        task2 = currnt;
    }
    
    
}

