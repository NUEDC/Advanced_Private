/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_DEFINE_H
#define __STM32F10x_DEFINE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
	 

#define GPIOA_SET                    1
#define GPIOB_SET                    2
#define GPIOC_SET                    3
#define GPIOD_SET                    4
#define GPIOE_SET                    5
#define GPIOF_SET                    6
#define GPIOG_SET                    7

#define pin0                         0
#define pin1                         1
#define pin2                         2
#define pin3                         3
#define pin4                         4
#define pin5                         5
#define pin6                         6
#define pin7                         7
#define pin8                         8
#define pin9                         9
#define pin10                       10
#define pin11                       11
#define pin12                       12
#define pin13                       13
#define pin14                       14
#define pin15                       15
#define pin16                       16

#define LOW_Speed                    2
#define MID_Speed                   10
#define HIGH_Speed                  50

typedef struct  
{
	char GPIO_PORT;       //引脚Port单独定义
	uint16_t GPIO_PIN;    //引脚Pin
	GPIOSpeed_TypeDef GPIO_Speed;  //引脚速度
	GPIOMode_TypeDef GPIO_Mode;  //引脚模式
	
}GPIO_CFG;


#endif
