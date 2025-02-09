/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_rtc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_dma.h"

#include "stm32f1xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define BATTERY_PACK_COUNT 2
#define BATTERY_COUNT_IN_PACK 2
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
int tmain(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define BMS5_Pin GPIO_PIN_1
#define BMS5_GPIO_Port GPIOA
#define BMS6_Pin GPIO_PIN_2
#define BMS6_GPIO_Port GPIOA
#define BMS3_Pin GPIO_PIN_3
#define BMS3_GPIO_Port GPIOA
#define BMS4_Pin GPIO_PIN_4
#define BMS4_GPIO_Port GPIOA
#define BMS1_Pin GPIO_PIN_5
#define BMS1_GPIO_Port GPIOA
#define BMS2_Pin GPIO_PIN_6
#define BMS2_GPIO_Port GPIOA
#define OW_Pin GPIO_PIN_7
#define OW_GPIO_Port GPIOA
#define PGOOD1_Pin GPIO_PIN_0
#define PGOOD1_GPIO_Port GPIOB
#define PGOOD2_Pin GPIO_PIN_1
#define PGOOD2_GPIO_Port GPIOB
#define DPC_RST_Pin GPIO_PIN_14
#define DPC_RST_GPIO_Port GPIOB
#define DPD_RST_Pin GPIO_PIN_15
#define DPD_RST_GPIO_Port GPIOB
#define LEDB5_Pin GPIO_PIN_5
#define LEDB5_GPIO_Port GPIOB
#define TIME_Pin GPIO_PIN_6
#define TIME_GPIO_Port GPIOB
#define TIME_EXTI_IRQn EXTI9_5_IRQn
#define I2C_INT_Pin GPIO_PIN_7
#define I2C_INT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
