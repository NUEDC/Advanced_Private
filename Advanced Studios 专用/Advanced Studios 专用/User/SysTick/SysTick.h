#ifdef __SYSTICK_H__
#define __SYSTICK_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#define uint unsigned int
#define uchar unsigned char


extern int SysTick_Init(uint8_t Timeus);//SysTick��ʼ������ �ж�ʱ�䣬�ж����ȼ�����װ�ؼĴ�����ֵ
extern int SysTick_Col(uint8_t Status);//����Systick״̬
extern uint8_t SysTick_IRQ_Function();//SysTick�жϷ�����
extern void Set_Counter(u8 Counter_Val);//���ü������Ĵ�����ֵ
extern void Systick_Fast_Set();//ϵͳ��ʱ����������
extern void Systick_Delay_us(__IO uint32_t us);//ϵͳ��ʱ����ʱ
extern void Systick_Delay_ms( __IO uint32_t ms);//ϵͳ��ʱ����ʱ
extern void TimingDelay_Decrement(void);//���Ļ�ȡ�����ж��е���


#endif
	
