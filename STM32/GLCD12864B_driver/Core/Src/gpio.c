/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|DRIVER_L2_Pin|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_RS_Pin|LCD_EN_Pin|GPIO_PIN_5|LCD_RW_Pin
                          |LCD_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|DRIVER_L1_Pin
                          |LCD_D3_Pin|LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin
                          |LCD_D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 DRIVER_L2_Pin PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|DRIVER_L2_Pin|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RS_Pin LCD_EN_Pin PA5 LCD_RW_Pin
                           LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_RS_Pin|LCD_EN_Pin|GPIO_PIN_5|LCD_RW_Pin
                          |LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D0_Pin LCD_D1_Pin LCD_D2_Pin DRIVER_L1_Pin
                           LCD_D3_Pin LCD_D4_Pin LCD_D5_Pin LCD_D6_Pin
                           LCD_D7_Pin */
  GPIO_InitStruct.Pin = LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|DRIVER_L1_Pin
                          |LCD_D3_Pin|LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin
                          |LCD_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

void MX_GPIO_Pin_Mode(GPIO_TypeDef  *GPIOx, uint16_t GPIO_Pin, uint8_t mode){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	// 1. De-initialize the pin first (optional but recommended)
	HAL_GPIO_DeInit(GPIOx, GPIO_Pin);

	if(mode){
		// 2. Reconfigure it as input
		GPIO_InitStruct.Pin = GPIO_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;  // Or GPIO_PULLUP / GPIO_PULLDOWN
		HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
	}
	else{
		GPIO_InitStruct.Pin = GPIO_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-pull output
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
	}
}

/* USER CODE END 2 */
