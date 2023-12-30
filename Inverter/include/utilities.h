#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <Arduino.h>

typedef struct Inverter_properties
{
    bool Status;
    float output_freq; // 50Hz
    float input_freq;
    int carrier_freq; //7KHz
    float batt_volt;
    float output_power;
    int input_AC;
    int output_AC;
}Inv_Data;

#ifdef BUTTONS_ENABLED
    #include "button_keys.c"
#endif

#ifdef KEYPAD_ENABLED
    #include "Keypad.c"
#endif

#ifdef LCD_ENABLED
    #include "display.hpp"
#endif

#ifdef LED_ENABLED
    #include "led_display.c"
#endif

#endif