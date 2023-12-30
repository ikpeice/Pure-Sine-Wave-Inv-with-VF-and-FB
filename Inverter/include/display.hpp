#ifndef DISPLAY_HPP
#define DISPLAY_HPP

//#include <main.h>
#include <utilities.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>


class Display
{
protected:
    
    /* data */
public:
    Display();
    //Display(Inv_Data *_data);
    ~Display();
    void begin(Inv_Data *_data);
    void show(int key);
    void clear();
};

class Lines: Display{
private:


    String *a, *b;
public:
    Lines(String* _a, String* _b):
    a(_a),b(_b)
    {

    }
    void show();
    void update();
};







#endif