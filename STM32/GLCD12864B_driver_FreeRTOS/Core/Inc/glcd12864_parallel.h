/*
 * glcd12864_parallel.h
 *
 *  Created on: Jul 24, 2025
 *      Author: echij
 */

#ifndef INC_GLCD12864_PARALLEL_H_
#define INC_GLCD12864_PARALLEL_H_

#include "main.h"

#define FONTHEIGHT 8

#define ST7920_WIDTH 128
#define ST7920_HEIGHT 64

#define LCD_RS_GPIO GPIOA
#define LCD_RS_PIN  GPIO_PIN_0
#define LCD_E_GPIO  GPIOA
#define LCD_E_PIN   GPIO_PIN_1
#define LCD_RST_GPIO GPIOA
#define LCD_RST_PIN  GPIO_PIN_10
#define LCD_RW_PIN	GPIO_PIN_8
#define LCD_RW_GPIO GPIOA
#define LCD_DATA_GPIO GPIOB

void lcd_write(char, unsigned char);
char lcd_read(char);
void set_rs(char);
void set_e(char);
void set_rw(char);
int is_lcd_busy(void);
void lcd_init(void);
void lcd_cls(void);
void lcd_putchar(int, int, unsigned char, int);
void lcd_putchar2(int, int, unsigned char, int);
void lcd_putchar3(int, int, unsigned char, int);
void lcd_putstring_a(int, int, char*, int, int);
void lcd_putstring_b(int, int, char*, int);
void lcd_putnumber(int, int, long, int, int, int);

void lcd_draw_pattern(uint8_t x, uint8_t y, const uint8_t *pattern, uint8_t width, uint8_t height);
void lcd_draw_fullscreen_x(void);
void lcd_update(void);
void lcd_clear_buffer(void);
void lcd_puts(uint8_t x, uint8_t y, const char *str);
void lcd_puts_3x5(uint8_t x, uint8_t y, const char *str);


void lcd_draw_bitmap(void) ;
//void lcd_draw_bitmap_only(void);
void lcd_draw_pointer(uint8_t x, uint8_t y);
void lcd_draw_topbar(void);
void lcd_draw_H_line(uint8_t x, uint8_t y, uint8_t lenght);
void lcd_draw_V_line(uint8_t x, uint8_t y, uint8_t lenght);
void lcd_draw_signalStrenght(uint8_t value);
void lcd_draw_battery(uint8_t x, uint8_t y, uint8_t value);

//STRING FUNCTIONS
int int2asc(long, int, char*, int);

#endif /* INC_GLCD12864_PARALLEL_H_ */
