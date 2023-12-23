#ifndef SINE_WAVE_H
#define SINE_WAVE_H

#include <Arduino.h>




class SPWM{
    
private:
//Receiver 
    long period;
    bool flag=true;
    bool buffer[1000];
    char bit = 1;
    bool debug = false;
// Transmitter

    int _carrier_period;
    int _carrier_freq;
    int _output_freq;
    //#define teta(V) (V*(9.0/2.0))
    #define TetaToradian(T) ((T*PI)/180)
    #define solve(teta) (abs(sin(teta)))



private:
    void setup_freq();
    int len(char s[]);
    char intTochar(int num);
    


public:

    SPWM(int output_freq, int carrier_freq);
    ~SPWM();
    void floatTocharArray(char *s, double num);
    void begin( bool verbros);
    void start();
    void stop();
    void set_freq(int frequency);
    

};



#endif