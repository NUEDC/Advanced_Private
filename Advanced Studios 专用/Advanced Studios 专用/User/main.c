#include "stm32f10x.h"
#include "stm32f10x_define.h"
#include "tim_config.h"
#include "uart.h"
int main(void)
{
	double tim;
	Fast_UART_SET(UART1_SET);
	set_P_S_VECTOR(USART1);
	FTM_GET_Config(FTM_IN1,FTM_IN1_CH1,UP_Edge);
  while(1)
  {	
		FTM_Time_Transfer();
  }
}
/*********************************************END OF FILE**********************/

