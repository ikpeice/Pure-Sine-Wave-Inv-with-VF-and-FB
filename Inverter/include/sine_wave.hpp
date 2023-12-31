#ifndef SINE_WAVE_HPP
#define SINE_WAVE_HPP

#include <Arduino.h>
#include "utilities.h"


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
    Inv_Data *_inv_data;


public:
    SPWM(Inv_Data *data);
    ~SPWM();
    void floatTocharArray(char *s, double num);
    void begin(bool verbros);
    void start();
    void soft_start(int _delay);
    void stop();
    bool set_output_freq(int output_freq);
    bool set_carrier_freq(int carrier_freq);
    void set_amplitude(float percent);
    void set_amplitude(int fb);

};



#endif