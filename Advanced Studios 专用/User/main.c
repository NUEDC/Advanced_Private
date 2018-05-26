#include "stm32f10x.h"
#include "GPIO_Config.h"
#include "UART.h"
#include "SysTick.h"
#include "stm32f10x_define.h"

int main(void)                  
{ 
	CLK_SET(GPIOB_SET);
	GPIO_INIT(GPIOB,pin0,HIGH_Speed,6);
	GPIO_OUT(GPIOB,GPIO_Pin_0,Bit_SET);
	Systick_Fast_Set();
	while(1)
	{
		GPIO_OUT(GPIOB,GPIO_Pin_0,Bit_RESET);
		Systick_Delay_ms(1000);
		GPIO_OUT(GPIOB,GPIO_Pin_0,Bit_SET);
		Systick_Delay_ms(1000);
	}
}
