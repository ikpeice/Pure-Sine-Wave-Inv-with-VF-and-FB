#ifndef SINE_WAVE_H
#define SINE_WAVE_H

#include <Arduino.h>




class SPWM{
    
private: 
// private variables

    int counterRegister = 1600; // 10KHz
    #define timer_increament 0.065 // us

    #define MAX_STEPS 222 // 45Hz
    #define MIN_STEPS 167 // 60Hz


    bool ON_flag=false;
    char feedback = 0;
    bool debug = false;

    int _carrier_period;
    int _carrier_freq;
    int _output_freq;

    #define TetaToradian(T) ((T*PI)/180)
    #define solve(teta) (abs(sin(teta)))



private: 
// private functions
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
    bool set_output_freq(int output_freq);
    bool set_carrier_freq(int carrier_freq);
    void set_amplitude(float percent);
    

};



#endif