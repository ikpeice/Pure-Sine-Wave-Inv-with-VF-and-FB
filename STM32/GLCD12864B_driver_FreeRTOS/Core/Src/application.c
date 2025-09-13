/*
 * application.c
 *
 *  Created on: Jul 31, 2025
 *      Author: echij
 */

#include "glcd12864b_driver.h"
#include "glcd12864_parallel.h"
#include "delay.h"
#include "bitmapimage.h"
#include "screens.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>




void vDisplay_Control(void *argument)
{
	  delay_init ();
	//  LCD_Init();
	//
	//  lcd_clear();
	//  HAL_Delay(1000);
	//
	////  drawFullGrid();
	////// drawTestPattern();
	//  drawString(1, 0, "HELLO STM32");
	//  drawString(1, 25, "GRAPHIC LCD");
	//  test_pixel();
	//  //drawFullGrid();
	//  st7920_update();


	  delay_ms(100);
	  lcd_init();
	  delay_ms(100);

	  lcd_cls();

	//


	  //lcd_draw_topbar();

	  lcd_puts_3x5(1,2,"MIRI AIR+ BLE CONNECTED");
	  lcd_draw_signalStrenght(89);

	  lcd_draw_battery(2,105,50);
	  lcd_draw_H_line(8,2,128);
	  lcd_draw_V_line(8,8,64);
	  lcd_update();


	//  lcd_puts(20,10,"HUMIDITY");
	//  lcd_puts(30,10,"PM 2.5");
	//  lcd_puts(40,10,"PM 10");
	//  lcd_puts(50,10,"CARBON DIOXIDE CO2");
	//  lcd_update();

  for(;;)
  {
	  //HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_7);
	  printf("Scree 1 running\n");
	  menu_screen();

	  vTaskDelay(1000);
  }
  /* USER CODE END Dispaly_Control */
}

void vLed_Control(void *argument){

	  for(;;)
	  {
		  HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_7);
		  printf("Led blinking\n");
		  vTaskDelay(1000);
	  }
}
