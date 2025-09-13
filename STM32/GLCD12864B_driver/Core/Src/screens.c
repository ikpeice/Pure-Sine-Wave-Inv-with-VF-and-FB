/*
 * ST7920_SERIAL.c
 *
 *  Created on: 07-Jun-2019
 *      Author: poe
 */

#include <screens.h>
#include "main.h"
#include "delay.h"
#include "glcd12864_parallel.h"

#include <stdbool.h>
#include <stdlib.h>

const char* parameters[]={
		"AIR TEMPERATURE",
		"RELATIVE HUMIDITY",
		"PM 2.5",
		"PM 10",
		"CARBO DIOXIDE (CO2)",
		"SO2",
		"CH4",
		"CH2O",
		"CO",
		"OZONE (O3)",
		"VOC"
};

extern uint8_t framebuffer[64][16];
uint8_t signal_ = 14;
uint8_t batt = 0;

void clear_screen(void) {
    for (uint8_t y = 10; y < 64; y++) {
        for (uint8_t x = 10; x < 128; x++) {
            uint8_t byte = x / 8;
            uint8_t bit = 7 - (x % 8);
            framebuffer[y][byte] &= ~(0x01 << bit);
        }
    }
}

void update_telemetry(){
	  lcd_draw_signalStrenght(signal_);
	  lcd_draw_battery(2,105,batt);
	  signal_ = random()%100;
	  batt = random()%100;

	  if(signal_>=100)signal_=14;
}

void menu_screen(){
	bool exit = false;
	uint8_t pointer_pos = 10, info_pos = 0;
	bool pointer_dir = false;

	while(!exit){
		clear_screen();
		update_telemetry();
		lcd_puts(10,10,parameters[info_pos + 0]);
		lcd_puts(20,10,parameters[info_pos + 1]);
		lcd_puts(30,10,parameters[info_pos + 2]);
		lcd_puts(40,10,parameters[info_pos + 3]);
		lcd_puts(50,10,parameters[info_pos + 4]);
		if(pointer_pos<=50 && pointer_pos>=10)lcd_draw_pointer(pointer_pos,0);
		lcd_update();
		HAL_Delay(1000);

		if(pointer_dir == false ){
			pointer_pos +=10;
			if(pointer_pos>50)info_pos++;
			if(pointer_pos >= 110)pointer_dir = true;
		}
		else if(pointer_dir == true ){
			pointer_pos -=10;
			if(pointer_pos>=50)info_pos--;
			if(pointer_pos <= 10)pointer_dir = false;
		}



	}
}

