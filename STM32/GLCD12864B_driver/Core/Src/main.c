/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "glcd12864b_driver.h"
#include "glcd12864_parallel.h"
#include "delay.h"
#include "bitmapimage.h"
#include "screens.h"

#include <stdlib.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


#define f_carrier 25000
#define f_fundamental_1 50
#define f_fundamental_2 67.5
#define TIMER_PERIOD 3599 //((72 MHz/25 KHz)/2)-1

const float PI = M_PI;
const float duty_coeff_1 = 0.741;
const float duty_coeff_2 = 1.0;
int Duty;
int k = 0;
int b = 0;
int f_fundamental;
int sampleNum;
float radVal;
float sineValue[1000];
float duty_coeff = duty_coeff_2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*Function for The Interrupt*/
void ISR_SINE(void) {
	if(b>1){
	  Duty = (int)(duty_coeff*TIMER_PERIOD*sineValue[k]);
	  if (k==0) {
		HAL_GPIO_WritePin(DRIVER_L1_GPIO_Port, DRIVER_L1_Pin, GPIO_PIN_RESET);
		TIM1->CCR1= 0;
	  }
	  if (k==(sampleNum/2)) {
		HAL_GPIO_WritePin(DRIVER_L2_GPIO_Port, DRIVER_L2_Pin, GPIO_PIN_RESET);
		TIM1->CCR1 = TIMER_PERIOD;
	  }
	  if (k>0 && k<(sampleNum/2))  {
		HAL_GPIO_WritePin(DRIVER_L2_GPIO_Port, DRIVER_L2_Pin, GPIO_PIN_SET);
		TIM1->CCR1 = Duty;
	  }
	  if (k>0 && k>(sampleNum/2) ) {
		HAL_GPIO_WritePin(DRIVER_L1_GPIO_Port, DRIVER_L1_Pin, GPIO_PIN_SET);
		TIM1->CCR1 = TIMER_PERIOD + Duty;
	  }
	  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	  k++;
	  if (k > sampleNum ) k=0;
	  b=0;
	}
	b++;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  sampleNum = (int)(f_carrier/f_fundamental_1);

  radVal = 2 * PI / sampleNum;

  for(int i=1;i<sampleNum+1;i++){
	      sineValue[i] = sin(radVal*(i));
  }

  delay_init ();
  TIM1->CCR1 = 1799;
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);

  //
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

  lcd_puts_3x5(1,2,"MIRI AIR+");
  lcd_draw_signalStrenght(89);

  lcd_draw_battery(2,105,50);
  lcd_draw_H_line(8,2,128);
  lcd_draw_V_line(8,8,64);
  lcd_update();

  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
//  lcd_puts(20,10,"HUMIDITY");
//  lcd_puts(30,10,"PM 2.5");
//  lcd_puts(40,10,"PM 10");
//  lcd_puts(50,10,"CARBON DIOXIDE CO2");
//  lcd_update();
  menu_screen();


//	lcd_clear_buffer();
//	lcd_puts(10, 5, "GLCD READY");
//	lcd_update_();  // push framebuffer to LCD

//  uint8_t signal = 14;
//  uint8_t batt = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //lcd_draw_bitmap();
//	  lcd_draw_pointer(9,0);
//	  delay_ms(50);
//	  lcd_draw_pointer(20,0);
//	  delay_ms(50);
//	  lcd_draw_pointer(30,0);
//	  delay_ms(50);
//	  lcd_draw_pointer(40,0);
//	  delay_ms(50);
//	  lcd_draw_pointer(50,0);

//	  lcd_putstring_a(0, 0, "LCD 12864 ST7920", 0, 1);
//	  lcd_putstring_a(1, 0, " CIA SPACE ", 0, 0);
//	  lcd_putstring_a(2, 0, "Graphical Fonts:", 0, 0);
//	  lcd_putstring_a(3, 0, "8x8px.", 0, 0);
//	  lcd_putstring_a(4, 1, "LCD", 0, 1);
//	  lcd_putstring_a(5, 1, "CIA SPACE ", 0, 0);
//	  lcd_putstring_a(6, 1, "Graphical", 0, 1);
//	  lcd_putstring_a(7, 1, "8x8px.", 0, 0);
//
//	  lcd_putstring_a(4, 0, "16x8px.", 1, 0);
//
//	  lcd_putstring_b(6, 0, "16x16px.", 1);


//	  lcd_draw_signalStrenght(signal);
//	  lcd_draw_battery(2,105,batt);
//	  lcd_update();
//	  signal = random()%100;
//	  batt = random()%100;
//
//	  if(signal>=100)signal=14;
	  HAL_Delay(100);
	  HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_7);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
