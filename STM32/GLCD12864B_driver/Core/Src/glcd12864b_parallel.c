/*
 * glcd12864b_parallel.c
 *
 *  Created on: Jul 24, 2025
 *      Author: echij
 */

#include "glcd12864_parallel.h"
#include "gpio.h"
#include "glcd12864b_driver.h"
#include "delay.h"
#include "fonts.h"
#include "stdlib.h"
#include "bitmapimage.h"

#include <stdbool.h>



#define LCD_CMD_MODE 0
#define LCD_DATA_MODE 1
/////////////////////////////////////
 // Functions for LCD12864 control  //
/////////////////////////////////////

uint8_t framebuffer[64][16]={0};  // 64 rows, 128/8 = 16 columns


void setPixel(uint8_t x, uint8_t y, uint8_t color) {
    if (x >= 64 || y >= 128) return;
    uint8_t page = y / 8;
    uint8_t bit  = 7 - (y % 8);  // top row is bit 7
    if (color)
        framebuffer[x][page] |=  (1 << bit);
    else
        framebuffer[x][page] &= ~(1 << bit);
}
//Write instruction (code==0) or data (code==1) to LCD
void lcd_write(char lcdmode, unsigned char value)
{
	//DDRD = 0xFF;     //Set port for write operation
//	uint8_t pin = 0x01;
//	for(int i = 0; i < 8; i++) {
//	    MX_GPIO_Pin_Mode(LCD_DATA_GPIO, pin, 0);
//	    pin <<= 1;  // Shift left by 1 for next iteration
//	}

	MX_GPIO_Pin_Mode(LCD_D0_GPIO_Port, LCD_D0_Pin, 0);
	MX_GPIO_Pin_Mode(LCD_D1_GPIO_Port, LCD_D1_Pin, 0);
	MX_GPIO_Pin_Mode(LCD_D2_GPIO_Port, LCD_D2_Pin, 0);
	MX_GPIO_Pin_Mode(LCD_D3_GPIO_Port, LCD_D3_Pin, 0);
	MX_GPIO_Pin_Mode(LCD_D4_GPIO_Port, LCD_D4_Pin, 0);
	MX_GPIO_Pin_Mode(LCD_D5_GPIO_Port, LCD_D5_Pin, 0);
	MX_GPIO_Pin_Mode(LCD_D6_GPIO_Port, LCD_D6_Pin, 0);
	MX_GPIO_Pin_Mode(LCD_D7_GPIO_Port, LCD_D7_Pin, 0);


	set_rw(0);	     //Write operation
	set_rs(lcdmode); //0 for instruction, 1 for data
	set_e(1);
	//PORTD = value;
//	LCD_DATA_GPIO->ODR = (LCD_DATA_GPIO->ODR & 0xFF00) | value;

	HAL_GPIO_WritePin(LCD_D0_GPIO_Port, LCD_D0_Pin, 0x01 & value);
	HAL_GPIO_WritePin(LCD_D1_GPIO_Port, LCD_D1_Pin, 0x01 & (value>>1));
	HAL_GPIO_WritePin(LCD_D2_GPIO_Port, LCD_D2_Pin, 0x01 & (value>>2));
	HAL_GPIO_WritePin(LCD_D3_GPIO_Port, LCD_D3_Pin, 0x01 & (value>>3));
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, 0x01 & (value>>4));
	HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, 0x01 & (value>>5));
	HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, 0x01 & (value>>6));
	HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, 0x01 & (value>>7));

    delay_us(10);
	set_e(0);

	set_rs(0);
}

//Read data from LCD
char lcd_read(char lcdmode)
{
	unsigned char value;

	//DDRD = 0x00;       //Set port for read operation
//	uint8_t pin = 0x01;
//	for(int i = 0; i < 8; i++) {
//	    MX_GPIO_Pin_Mode(LCD_DATA_GPIO, pin, 1);
//	    pin <<= 1;  // Shift left by 1 for next iteration
//	}
	//PORTD = 0xFF;      //Activate pull-up resistors to ensure proper data transmission

	MX_GPIO_Pin_Mode(LCD_D0_GPIO_Port, LCD_D0_Pin, 1);
	MX_GPIO_Pin_Mode(LCD_D1_GPIO_Port, LCD_D1_Pin, 1);
	MX_GPIO_Pin_Mode(LCD_D2_GPIO_Port, LCD_D2_Pin, 1);
	MX_GPIO_Pin_Mode(LCD_D3_GPIO_Port, LCD_D3_Pin, 1);
	MX_GPIO_Pin_Mode(LCD_D4_GPIO_Port, LCD_D4_Pin, 1);
	MX_GPIO_Pin_Mode(LCD_D5_GPIO_Port, LCD_D5_Pin, 1);
	MX_GPIO_Pin_Mode(LCD_D6_GPIO_Port, LCD_D6_Pin, 1);
	MX_GPIO_Pin_Mode(LCD_D7_GPIO_Port, LCD_D7_Pin, 1);

    set_rw(1);	       //Read operation
	set_rs(lcdmode);   //Get value 0: for busy flag, 1 for other data

	set_e(1);          //Read data
    delay_us(10);

    uint8_t data = 0;
    data |= HAL_GPIO_ReadPin(LCD_D0_GPIO_Port, LCD_D0_Pin);
    data |= HAL_GPIO_ReadPin(LCD_D1_GPIO_Port, LCD_D1_Pin)<<1;
    data |= HAL_GPIO_ReadPin(LCD_D2_GPIO_Port, LCD_D1_Pin)<<2;
    data |= HAL_GPIO_ReadPin(LCD_D3_GPIO_Port, LCD_D1_Pin)<<3;
    data |= HAL_GPIO_ReadPin(LCD_D4_GPIO_Port, LCD_D1_Pin)<<4;
    data |= HAL_GPIO_ReadPin(LCD_D5_GPIO_Port, LCD_D1_Pin)<<5;
    data |= HAL_GPIO_ReadPin(LCD_D6_GPIO_Port, LCD_D1_Pin)<<6;
    data |= HAL_GPIO_ReadPin(LCD_D7_GPIO_Port, LCD_D1_Pin)<<7;

//    value = LCD_DATA_GPIO->IDR;
	//value = PIND;
    set_e(0);

	//set_rs(0);

	return (char)data;
}

//Set RW line
void set_rw(char status)
{
    if(status)
	{
        //PORTC |= 2;
        HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_SET);
	}
    else
	{
	    //PORTC &= ~(2);
	    HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_RESET);
	}
}

//Set RS line
void set_rs(char status)
{
    if(status)
	{
        //PORTC |= 1;
        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
	}
    else
	{
	    //PORTC &= ~(1);
	    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	}
}

//Set E line
void set_e(char status)
{
    if(status)
	{
        //PORTC |= 4;
        HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
	}
    else
	{
	    //PORTC &= ~(4);
	    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);
	}
}

//Check for busy flag (BF)
int is_lcd_busy(void)
{
	int v = lcd_read(0);
	delay_us(10);
	v = lcd_read(0);

	if(v & 0x80)
	{
		return -1;
	}
	else
	{
		return 0;
	}

}



//void setPixel_(uint8_t x, uint8_t col, uint8_t color) {
//    if (x >= 128 || y >= 64) return;
//    uint8_t odd = 0;
//	if(col & 1) //Detect odd coloumn
//	{
//		odd = 1;
//	}
//    uint8_t byteIndex = x / 8;
//    uint8_t bitIndex  = 7 - (x % 8);
//    if (color)
//        framebuffer[y][byteIndex] |=  (1 << bitIndex);
//    else
//        framebuffer[y][byteIndex] &= ~(1 << bitIndex);
//}

//Send one character to LCD (Normal size)
//
void lcd_putchar(int row0, int col0, unsigned char ch0, int inv)
{
	int t1;
	int odd = 0;
	unsigned char v1, v2;
	int col = col0 / 2;
	int row = row0 * FONTHEIGHT;
	unsigned char ch;

	if(row & 0x20)  //Enter lower part of screen => go to next page
	{
        row &= ~0x20;
        col |= 8;
    }

	if(col0 & 1) //Detect odd coloumn
	{
		odd = 1;
	}

	for(t1 = 0; t1 < FONTHEIGHT; t1++)
    {
	    //Set address
        lcd_write(LCD_CMD_MODE, 0x80 + row + t1);
        lcd_write(LCD_CMD_MODE, 0x80 + col);

        //Get old values of 2 GDRAM bytes
	    v1 = lcd_read(1); // dummy read
        v1 = lcd_read(1);
        v2 = lcd_read(1);

        //Set address
        lcd_write(LCD_CMD_MODE, 0x80 + row + t1);
        lcd_write(LCD_CMD_MODE, 0x80 + col);

        if(!inv)
        {
			ch = font_5x8_[ch0][t1];//* FONTHEIGHT
		}
		else
        {
			ch = ~font_5x8_[ch0][t1];// * FONTHEIGHT
		}

        if(odd)
        {
            //Write data on RIGHT side of existing character
            lcd_write(LCD_DATA_MODE, v1);
            lcd_write(LCD_DATA_MODE, ch);
        }
        else
        {
			//Write data on LEFT side of existing character
            lcd_write(LCD_DATA_MODE, ch);
            lcd_write(LCD_DATA_MODE, v2);
        }
    }
}

//Send one character to LCD (DOUBLE size and normal width)
//
void lcd_putchar2(int row0, int col0, unsigned char ch0, int inv)
{
	int t1, t2;
	int odd = 0;
	unsigned char v1, v2;
	int col = col0 >> 1;
	int row = row0 * FONTHEIGHT;
	unsigned char ch;

	if(row & 0x20)  //Enter lower part of screen => go to next page
	{
        row &= ~0x20;
        col |= 8;
    }

	if(col0 & 1) //Detect odd coloumn
	{
		odd = 1;
	}

	for(t1 = 0; t1 < FONTHEIGHT; t1++)
    {
		if(!inv) //Calculate character position in array and xor invert number if needed
        {
			ch = (font_5x8[ch0 * FONTHEIGHT + t1]);
		}
		else
        {
			ch = (~font_5x8[ch0 * FONTHEIGHT + t1]);
		}

		for(t2 = 0; t2 < 2; t2++)
		{
	        //Set address
            lcd_write(LCD_CMD_MODE, 0x80 + row + t1 * 2 + t2);
            lcd_write(LCD_CMD_MODE, 0x80 + col);

            //Get old values of 2 GDRAM bytes
	        v1 = lcd_read(1);
            v1 = lcd_read(1);
            v2 = lcd_read(1);

            //Set address
            lcd_write(LCD_CMD_MODE, 0x80 + row + t1 * 2 + t2);
            lcd_write(LCD_CMD_MODE, 0x80 + col);

            if(odd)
            {
                //Write data on RIGHT side of existing character
                lcd_write(LCD_DATA_MODE, v1);
                lcd_write(LCD_DATA_MODE, ch);
            }
            else
            {
			    //Write data on LEFT side of existing character
                lcd_write(LCD_DATA_MODE, ch);
                lcd_write(LCD_DATA_MODE, v2);
            }
        }
    }
}

//Send one character to LCD (DOUBLE size and DOUBLE width)
//
void lcd_putchar3(int row0, int col0, unsigned char ch0, int inv)
{
	int t1, t2;
	unsigned char ch;
	//unsigned int i[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned int i[FONTHEIGHT] = {0, 0, 0, 0, 0, 0, 0, 0};
	int col = col0 >> 1;
	int row = row0 * FONTHEIGHT;

	if(row & 0x20)  //Enter lower part of screen => go to next page
	{
        row &= ~0x20;
        col |= 8;
    }


	for(t1 = 0; t1 < FONTHEIGHT; t1++)
    {
		if(!inv) //Calculate character position in array and xor invert number if needed
        {
			ch = (font_5x8[ch0 * FONTHEIGHT + t1]);
		}
		else
        {
			ch = (~font_5x8[ch0 * FONTHEIGHT + t1]);
		}

		//Double 8 to 16 bits
	    i[t1] = 0;
		for(t2 = 7; t2 > -1; t2--)
		{
			if(ch & (1 << t2))
			{
				i[t1] += (1 << ((t2 << 1) + 1)) + (1 << (t2 << 1)); //Double bit pattern 2 by 1
			}
		}
	}

	t2 = 0;
	for(t1 = 0; t1 < FONTHEIGHT; t1++)
	{
		for(t2 = 0; t2 < 2; t2++)
		{
	        //Set address
            lcd_write(LCD_CMD_MODE, 0x80 + row + t1 * 2 + t2);
            lcd_write(LCD_CMD_MODE, 0x80 + col);

            lcd_write(LCD_DATA_MODE, ((i[t1] >> 8) & 0xFF));
            lcd_write(LCD_DATA_MODE, i[t1] & 0xFF);
            //lcd_putnumber(t1, 0, i[t1] , -1, 0, 0);
        }
    }

}

//Send string (\0 terminated) to LCD normal or double height
void lcd_putstring_a(int row, int col, char *s, int size, int inv)
{
    unsigned char t1;

    for(t1 = col; *(s); t1++)
	{
		if(!size)
		{
            lcd_putchar(row, t1, *(s++), inv);
        }
        else
        {
            lcd_putchar2(row, t1, *(s++), inv);
        }
	}
}

//String in DOUBLE height and DOUBLE width
void lcd_putstring_b(int row, int col, char *s, int inv)
{
    unsigned char t1;

    for(t1 = col; *(s); t1++)
	{
	    lcd_putchar3(row, t1 * 2, *(s++), inv);
	}
}

//Clear LCD
void lcd_cls(void)
{
	int x, y,x1;
    for(x = 0; x < 64; x++)
    {
		for(y = 0; y < 16; y++)
		{
			if(x > 31)  //Enter lower part of screen => go to next page
			{
		        x1 = x % 32;
		        //y |= 8;
				//Set address
	            lcd_write(LCD_CMD_MODE, 0x80 | x1);
	            lcd_write(LCD_CMD_MODE, 0x80 | y);
		    }
			else{
				//Set address
	            lcd_write(LCD_CMD_MODE, 0x80 | x);
	            lcd_write(LCD_CMD_MODE, 0x80 | y);
			}


            //Write data
            lcd_write(LCD_DATA_MODE, 0);
            lcd_write(LCD_DATA_MODE, 0);
        }
    }
}




//Init LCD
void lcd_init(void)
{
    //Reset
    //PORTC &= ~(8);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
    delay_ms(1);
    //PORTC |= 8;
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    delay_ms(40);

    lcd_write(LCD_CMD_MODE, 0x30);	//Use 8-bit mode parallel
    delay_ms(1);

    lcd_write(LCD_CMD_MODE, 0x0C); //All on Cursor on, Blink on , Display on
    delay_ms(1);

    lcd_write(LCD_CMD_MODE, 0x01); //Perform CLS in text mode to eliminate random chars from screen
    delay_ms(20);

    lcd_write(LCD_CMD_MODE, 0x34); //Switch to extended mode, redefine function set
    delay_us(1000);

    lcd_write(LCD_CMD_MODE, 0x36); //Add graphic mode
    delay_us(1000);

    lcd_write(LCD_CMD_MODE, 0x12); //Display control and display ON
    delay_us(1000);
}


void lcd_draw_bitmap(void) {

	uint8_t ch0;
	uint8_t ch1;
    for (uint8_t row = 0; row < 64; row++) {



    	for(int col = 0; col < 16; col++){

        	if(row > 31)  //Enter lower part of screen => go to next page
        	{
                uint8_t row_ = row % 32;
                col |= 8;
                lcd_write(LCD_CMD_MODE, 0x80 + row_);
                lcd_write(LCD_CMD_MODE, 0x80 + col);


            }
        	else{
                lcd_write(LCD_CMD_MODE, 0x80 + row);
                lcd_write(LCD_CMD_MODE, 0x80 + col);
        	}

//            ch0 = topbar_bitmap[row][col*2];
//            ch1 = topbar_bitmap[row][(col*2)+1];

            lcd_write(LCD_DATA_MODE, ch0);
            lcd_write(LCD_DATA_MODE, ch1);
    	}
    }
}

void lcd_draw_pointer(uint8_t new_x, uint8_t new_y) {
	static uint8_t prev_x = 9;
	static uint8_t prev_y = 0;
	static uint8_t prev_buff[1][7]={0};

	if(new_x > 57)new_x = 57;
	if(new_y > 15)new_y = 15;


    for (uint8_t row = 0; row < 7; row++) {
    	for(int col = 0; col < 1; col++){
        	framebuffer[prev_x + row][prev_y + col] = prev_buff[col][row];
    	}
    }

    for (uint8_t row = 0; row < 7; row++) {
    	for(int col = 0; col < 1; col++){
        	prev_buff[col][row] = framebuffer[new_x + row][new_y + col];
    	}
    }

    for (uint8_t row = 0; row < 7; row++) {
    	for(int col = 0; col < 1; col++){
    		framebuffer[new_x + row][new_y + col] = pointer_bitmap[col][row];
    	}
    }

    prev_x = new_x;
    prev_y = new_y;
}

void lcd_draw_topbar(void){
    for (uint8_t row = 0; row < 7; row++) {
        for (uint8_t col = 0; col < 39; col++) {
            uint8_t byte = col / 8;
            uint8_t bit = 7 - (col % 8);

            // Read corresponding bit from miriair_bitmap
            uint8_t src_byte = miriair_bitmap[row][byte];
            uint8_t bit_val = (src_byte >> bit) & 0x01;

            if (bit_val)
                framebuffer[row][byte] |=  (1 << bit);
            else
                framebuffer[row][byte] &= ~(1 << bit);
        }
    }
}

void lcd_draw_H_line(uint8_t x, uint8_t y, uint8_t lenght){
	for(int col = y; col < lenght; col++){
		if(col==128)break;
		uint8_t page = col / 8;
		uint8_t bit = 7 - (col % 8);
		framebuffer[ x][page] |= (0x01 << bit);
	}
}

void lcd_draw_V_line(uint8_t x, uint8_t y, uint8_t lenght){
	uint8_t page = y / 8;
	uint8_t bit = 7 - (y % 8);
    for (uint8_t row = x; row < lenght; row++) {
    	if(x==64)break;
    	framebuffer[ row][page] |= (0x01 << bit);
    }
}

void lcd_draw_signalStrenght(uint8_t value){

	uint8_t page = 15;
	uint8_t y = 121;
	uint8_t num_bars = 7- (value/14);

    for(uint8_t row = 0; row < 7; row++) {
    	for(uint8_t col = y; col < 128; col++){
    		uint8_t bit = 7 - (col % 8);
    			framebuffer[ row][page] &= ~(0x01 << bit); // clear the bit
    		//lcd_update();
    	}
    }

	if(value < 14){
	    for(uint8_t row = 0; row < 7; row++) {
	    	for(uint8_t col = y; col < 128; col++){
	    		uint8_t bit = 7 - (col % 8);
	    		if(row == (col - y)){
	    			framebuffer[ row][page] |= (0x01 << bit); // set the bit
	    			framebuffer[ row][page] |= (0x01 << (6 - bit)); // set the bit
	    			break;
	    		}
	    		else{
	    			framebuffer[ row][page] &= ~(0x01 << bit); // clear the bit
	    		}
	    		//lcd_update();
	    	}
	    	//if(row==0)break;
	    	//y++;
	    }
	}
	else{

	    for(uint8_t row = 6; row >= 0; row--) {
	    	for(uint8_t col = y; col < 128; col++){
	    		uint8_t bit = 7 - (col % 8);
	    		if(bit < num_bars){
	    			framebuffer[ row][page] &= ~(0x01 << bit); // clear the bit
	    		}
	    		else{

	    			framebuffer[ row][page] |= (0x01 << bit); // set the bit
	    		}
	    		//lcd_update();
	    	}
	    	if(row==0)break;
	    	y++;
	    }
	}

}

void lcd_draw_battery(uint8_t x, uint8_t y, uint8_t value){

	uint8_t level = 11 - (value / 10);
    for (uint8_t row = x; row < (x + 5); row++) {
        for (uint8_t col = y; col < y+12; col++) {
            uint8_t byte = col / 8;
            uint8_t bit = 7 - (col % 8);

            // Read corresponding bit from miriair_bitmap
            uint8_t src_byte = battery_bitmap[row-x][(col-y)/8];
            uint8_t bit_num = 7 -  ((col - y) % 8);
            uint8_t bit_val = (src_byte >> bit_num) & 0x01;

            if (bit_val || (col - y) >= level)
                framebuffer[row][byte] |=  (1 << bit);
            else
                framebuffer[row][byte] &= ~(1 << bit);

            //lcd_update();
        }

    }

}


void lcd_update(void) {
	uint8_t ch0;
	uint8_t ch1;
	uint8_t row_;
    for (uint8_t row = 0; row < 64; row++) {

    	for(int col = 0; col < 8; col++){
            row_ = row % 32;
            uint8_t col_ = col;
        	if(row >= 32)  //Enter lower part of screen => go to next page
        	{
                col_ |= 0x08;
//                lcd_write(LCD_CMD_MODE, 0x80 | row_);
//                lcd_write(LCD_CMD_MODE, 0x80 | col);
            }
//        	else{
//
//        	}

        	lcd_write(LCD_CMD_MODE, 0x80 | row_);
        	lcd_write(LCD_CMD_MODE, 0x80 + col_);

            ch0 = framebuffer[row][col*2];
            ch1 = framebuffer[row][(col*2)+1];


            lcd_write(LCD_DATA_MODE, ch0);
            lcd_write(LCD_DATA_MODE, ch1);
    	}
    }
}

void lcd_clear_buffer(void) {
    for (uint8_t y = 0; y < 64; y++) {
        for (uint8_t x = 0; x < 16; x++) {
            framebuffer[y][x] = 0x00;
        }
    }
}



void lcd_putchar_(uint8_t x, uint8_t y, char c) {
    if (c < 32 || c > 126) return;
    const uint8_t *bitmap = font_5x7[c - 32];
    uint8_t bits=0;
    for (uint8_t row = 0; row < 7; row++) {
    		bits = bitmap[row];
        for (uint8_t col = 0; col < 5; col++) {  // 5 visible columns
            if (bits & (1 << (4 - col))) {       // MSB on left
                setPixel(x + row, y + col, 1);   // x grows right, y grows down
            }

        }
    }
}

void lcd_putchar_3x5(uint8_t x, uint8_t y, char c) {
    if (c < 32 || c > 0x5A) return;

    if (c >= 'a' && c <= 'z') c -= 32;

    const uint8_t *bitmap = font_3x5[c - 32];
    uint8_t bits=0;
    for (uint8_t row = 0; row < 5; row++) {
    		bits = bitmap[row];
        for (uint8_t col = 0; col < 3; col++) {  // 5 visible columns
            if (bits & (1 << (2 - col))) {       // MSB on left
                setPixel(x + row, y + col, 1);   // x grows right, y grows down
            }

        }
    }
}




void lcd_puts(uint8_t x, uint8_t y, const char *str) {
    while (*str && y < (128 - 6)) { // stop early if too close to right edge
        lcd_putchar_(x, y, *str++);
        y += 6;  // 5-pixel char + 1 space
    }
}

void lcd_puts_3x5(uint8_t x, uint8_t y, const char *str){
    while (*str && y < (128 - 6)) { // stop early if too close to right edge
        lcd_putchar_3x5(x, y, *str++);
        y += 4;  // 5-pixel char + 1 space
    }
}



