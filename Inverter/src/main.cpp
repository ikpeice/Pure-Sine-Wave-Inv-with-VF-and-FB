#define BUTTONS_ENABLED

#include <main.h>
#include <sine_wave.hpp>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x07,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int output_freq = 50; // 50Hz
int carrier_freq = 15; //7KHz
SPWM inverter(output_freq, carrier_freq);


long currnt,task1,task2;
bool ON = false;

int feedback_pin = A0;


void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Smart Inverter");

    inverter.begin(true);
    delay(50);
    //inverter.set_amplitude(1);
    inverter.soft_start();
    pinMode(up_button,INPUT);
    pinMode(enter_button,INPUT);
    pinMode(down_button,INPUT);
    pinMode(led,OUTPUT);
    
}

void loop() {
    currnt = millis();
    if((currnt-task1) > 10){
        //lcd.clear();
        lcd.setCursor(0,1);
        int d = analogRead(feedback_pin);
        float c = 0.09775*d;
        lcd.print(c);
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

