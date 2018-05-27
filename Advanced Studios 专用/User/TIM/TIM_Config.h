#ifdef __TIM_CONFIG_H__
#define __TIM_CONFIG_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#define uint unsigned int
#define uchar unsigned char
	

//参数定义

#define BASIC_TIM_CLK_Cmd    RCC_APB1PeriphClockCmd  //基本定时器时钟控制函数


//返回变量声明
/************基本定时器 TIM6&TIM7**********/
/*使用初始化要初始化NVIC和TIM一起*/
extern void Basic_TIM_Config(uint8_t TIMx,uint16_t Period, uint16_t Psc);      //基本定时器初始化
extern void Basic_TIM_NVIC_Config(uint TIM_NUM); //基本定时器中断配置函数
extern int Basic_TIM_IRQ_Function();//基本定时器中断服务函数
extern void Basic_TIM_Col(uint8_t Status);         //基本定时器控制函数

/************通用定时器 TIM2~TIM5**********/




/************高级定时器 TIM1&TIM8**********/




//函数声明

#endif
