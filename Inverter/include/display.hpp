#ifndef DISPLAY_HPP
#define DISPLAY_HPP

//#include <main.h>
#include <utilities.h>
#include <LiquidCrystal_I2C.h>


class Display
{
private:
    
    /* data */
public:
    Display(Inv_Data *_data);
    ~Display();
    void begin();
    void show(int key);
    void clear();
};

class Lines{
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