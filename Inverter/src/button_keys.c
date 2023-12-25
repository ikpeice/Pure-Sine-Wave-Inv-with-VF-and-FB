
#include <Arduino.h>

/*Keypad pin setup*/
#define up_button 22
#define enter_button 23
#define down_button 24
enum key{
    UP_KEY = 1,
    ENTER_KEY,
    DOWN_KEY
};

int get_key(){
    if(digitalRead(up_button)){
        return UP_KEY;
    }
    else if(digitalRead(enter_button)){
        return ENTER_KEY;
    }
    else if(digitalRead(down_button)){
        return DOWN_KEY;
    }
    else{
        return 0;
    }
}
