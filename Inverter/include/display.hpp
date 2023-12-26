#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <main.h>
#include <utilities.h>
#include <LiquidCrystal_I2C.h>


class Display
{
private:
    
    /* data */
public:
    Display(/* args */);
    ~Display();
    void start();
    void page1();
};




#endif