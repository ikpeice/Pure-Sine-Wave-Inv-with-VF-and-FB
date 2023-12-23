#include <Arduino.h>
#include <sine_wave.hpp>

// int _output_freq = 50;
// int _carrier_period;
// int carrier_freq = 10;
// #define timer_increament 0.0625

SPWM inverter(50,10);

void setup() {
Serial.begin(9600);

// _carrier_period = (1/(float)carrier_freq) * 1000;
// int counterRegister = _carrier_period/timer_increament;
// float step = (1/(float)_output_freq)*1000;
// int steps = (step / ((float)_carrier_period))*1000;
// float slope = 180/((float)steps/2);
// Serial.print("carrier p = ");
// Serial.println(_carrier_period);
// Serial.print("register = ");
// Serial.println(counterRegister);
// Serial.print("steps = ");
// Serial.println(slope*51);
inverter.begin(true);
delay(1000);
inverter.start();

}

void loop() {

}

