#ifdef __SYSTICK_H__
#define __SYSTICK_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#define uint unsigned int
#define uchar unsigned char


extern int SysTick_Init(uint8_t Timeus);//SysTick初始化函数 中断时间，中断优先级。重装载寄存器初值
extern int SysTick_Col(uint8_t Status);//控制Systick状态
extern uint8_t SysTick_IRQ_Function();//SysTick中断服务函数
extern void Set_Counter(u8 Counter_Val);//设置计数器寄存器初值
extern void Systick_Fast_Set();//系统定时器快速设置
extern void Systick_Delay_us(__IO uint32_t us);//系统定时器延时
extern void Systick_Delay_ms( __IO uint32_t ms);//系统定时器延时
extern void TimingDelay_Decrement(void);//节拍获取，在中断中调用


#endif
	
