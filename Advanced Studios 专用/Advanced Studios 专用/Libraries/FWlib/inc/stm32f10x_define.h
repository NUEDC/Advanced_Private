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


#define High                         1
#define Low                          0


#define UART0_SET                    0
#define UART1_SET                    1
#define UART2_SET                    2
#define UART3_SET                    3
#define UART4_SET                    4
#define UART5_SET                    5


/*Systick Define*/
#define Set_ENABLE                   1
#define Set_DISABLE                  0


/*Basic TIM*/
#define BASIC_TIM_6                  6
#define BASIC_TIM_7                  7
#define BASIC_TIM_6_CLK              RCC_APB1Periph_TIM6
#define BASIC_TIM_7_CLK              RCC_APB1Periph_TIM7
#define BASIC_TIM_6_IRQ              TIM6_IRQn
#define BASIC_TIM_7_IRQ              TIM7_IRQn
#define BASIC_TIM_6_IRQHandler       TIM6_IRQHandler
#define BASIC_TIM_7_IRQHandler       TIM7_IRQHandler


/*General TIM*/
#define GENERAL_TIM_2                2
#define GENERAL_TIM_3                3
#define GENERAL_TIM_4                4
#define GENERAL_TIM_5                5

#define TIM_Mode_Up                  1
#define TIM_Mode_Down                2

/*****FTM*******/

#define FTM0                         0

#define FTM0_CH1                     1
#define FTM0_CH2                     2
#define FTM0_CH3                     3
#define FTM0_CH4                     4

#define FTM1                         1

#define FTM1_CH1                     1
#define FTM1_CH2                     2
#define FTM1_CH3                     3
#define FTM1_CH4                     4

#define FTM2                         2

#define FTM2_CH1                     1
#define FTM2_CH2                     2
#define FTM2_CH3                     3
#define FTM2_CH4                     4

#define FTM3                         3

#define FTM3_CH1                     1
#define FTM3_CH2                     2
#define FTM3_CH3                     3
#define FTM3_CH4                     4


#define GENERAL_TIM_Prescaler        71


/*FTM_GET*/

#define FTM_IN0                      0

#define FTM_IN0_CH1                  1
#define FTM_IN0_CH2                  2
#define FTM_IN0_CH3                  3
#define FTM_IN0_CH4                  4

#define FTM_IN1                      1

#define FTM_IN1_CH1                  1
#define FTM_IN1_CH2                  2
#define FTM_IN1_CH3                  3
#define FTM_IN1_CH4                  4

#define FTM_IN2                      2

#define FTM_IN2_CH1                  1
#define FTM_IN2_CH2                  2
#define FTM_IN2_CH3                  3
#define FTM_IN2_CH4                  4

#define FTM_IN3                      3

#define FTM_IN3_CH1                  1
#define FTM_IN3_CH2                  2
#define FTM_IN3_CH3                  3
#define FTM_IN3_CH4                  4


#define UP_Edge                      TIM_ICPolarity_Rising
#define FALL_Edge                    TIM_ICPolarity_Falling

#define FTM_IN_PERIOD                0xFFFF
#define FTM_IN_PSC                   71

/*中断相关*/
#define GENERAL_TIM_IT_CCx           TIM_IT_CC1
#define NVIC_FTM_IN0                 TIM2_IRQn
#define NVIC_FTM_IN1                 TIM5_IRQn
#define NVIC_FTM_IN2                 TIM3_IRQn
#define NVIC_FTM_IN3                 TIM3_IRQn

/**********************************/
typedef struct  
{
	char GPIO_PORT;       //引脚Port单独定义
	uint16_t GPIO_PIN;    //引脚Pin
	GPIOSpeed_TypeDef GPIO_Speed;  //引脚速度
	GPIOMode_TypeDef GPIO_Mode;  //引脚模式
	
}GPIO_CFG;
/**************FTM捕获结构体*****************/
// 定时器输入捕获用户自定义变量结构体定义
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // 捕获结束标志位
	uint8_t   Capture_StartFlag;    // 捕获开始标志位
	uint16_t  Capture_CcrValue;     // 捕获寄存器的值
	uint16_t  Capture_Period;       // 自动重装载寄存器更新标志 
}TIM_ICUserValueTypeDef;



#endif
