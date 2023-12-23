#include <Arduino.h>
#include <sine_wave.hpp>

#define output_freq 50 // 60Hz
#define carrier_freq 20 //7KHz

SPWM inverter(output_freq, carrier_freq);

void setup() {
Serial.begin(9600);
inverter.begin(true);
delay(1000);
inverter.start();

}

void loop() {
    delay(1000);
    inverter.stop();
    delay(1000);
    inverter.start();
}

