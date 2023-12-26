#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <Arduino.h>

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