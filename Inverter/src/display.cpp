//#define LCD_ENABLED
//#include <utilities.h>
#include <display.hpp>

LiquidCrystal_I2C lcd(0x07,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Display::Display(/* args */)
{
}

Display::~Display()
{
}

void Display::start(){
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("--SMART INVERTER--");
    lcd.setCursor(0,1);
    lcd.print("Vwersion 1.1.2");
}

void Display::page1(){
    
}

