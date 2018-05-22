#include "stm32f10x.h"
#include "GPIO_Config.h"
#include "UART.h"
#include "stm32f10x_define.h"

int main(void)                  
{ 
	CLK_SET(GPIOB_SET);
	GPIO_INIT(GPIOB,pin5,HIGH_Speed,6);
	GPIO_OUT(GPIOB,GPIO_Pin_5,Bit_RESET);
}
