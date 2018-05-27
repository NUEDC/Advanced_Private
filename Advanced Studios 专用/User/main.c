#include "stm32f10x.h"
#include "stm32f10x_define.h"
#include "GPIO_Config.h"
#include "Systick.h"
#include "UART.h"
#include "TIM_Config.h"


volatile uint32_t time = 0; // ms 计时变量 


int main(void)
{
	
	CLK_SET(GPIOB_SET);
	GPIO_INIT(GPIOB,pin0,HIGH_Speed,6);
	GPIO_OUT(GPIOB,GPIO_Pin_0,Bit_RESET);
	Basic_TIM_NVIC_Config(BASIC_TIM_6);
	Basic_TIM_Config(BASIC_TIM_6,1000-1,71);
	Basic_TIM_Col(Set_ENABLE);
	
  while(1)
  {
    if ( time == 1000 )
    {
      time = 0;
      OUT_TOGGLE(GPIOB,pin0);
    }        
  }
}
/*********************************************END OF FILE**********************/

