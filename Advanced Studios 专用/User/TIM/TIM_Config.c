#include "stm32f10x.h"
#include "TIM_Config.h"
#include "GPIO_Config.h"
#include "stm32f10x_define.h"
#define uint unsigned int

extern volatile uint32_t time;

#define BASIC_TIM_CLK_Cmd    RCC_APB1PeriphClockCmd  //基本定时器时钟控制函数


typedef struct  
{
  TIM_TypeDef* TIM_Data;
	uint8_t NVIC_CH;
}TIM_INFMATION;

TIM_INFMATION TIM_CODE;



/*具体的细节定义见stm32f10x_define.h*/

/*
定时器状态控制函数可以开启和关闭
 void Basic_TIM_Col(uint8_t Status)
                           状态
Status   Set_ENABLE   Set_DISABLE
TIM_TypeDef* TIMx
*/
void Basic_TIM_Col(uint8_t Status)
{
	switch(Status)
	{
		case 0:
		TIM_ITConfig(TIM_CODE.TIM_Data,TIM_IT_Update,DISABLE);
		TIM_Cmd(TIM_CODE.TIM_Data, DISABLE);	
		break;
		case 1:
		TIM_ITConfig(TIM_CODE.TIM_Data,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM_CODE.TIM_Data, ENABLE);	
		break;
	}
}


/******基本定时器部分******/
/*
基本定时器TIM6&TIM7初始化函数
Basic_TIM_Config(uint8_t TIMx,uint8_t Period, uint8_t Psc)
                      TIM        定时器周期       分频因子
  TIMx   BASIC_TIM_6  BASIC_TIM_7
  Period  计算得到 如果Psc=71 时钟 1MHz  Period = 1000 时为计数周期1ms
  Psc   一般为71； 系统时钟-1
注意：次函数没有开启定时器，仅仅是初始化，需要再次Enable
*/
void Basic_TIM_Config(uint8_t TIMx,uint16_t Period, uint16_t Psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	switch(TIMx)
	{
		case 1:
			BASIC_TIM_CLK_Cmd(RCC_APB1Periph_TIM6,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
		  TIM_TimeBaseStructure.TIM_Prescaler = Psc;
		  TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
			TIM_ClearFlag(TIM6,TIM_FLAG_Update);
		  Basic_TIM_Col(Set_DISABLE);
			TIM_CODE.TIM_Data = TIM6;
		  TIM_CODE.NVIC_CH = TIM6_IRQn;
			break;
		case 2:
			BASIC_TIM_CLK_Cmd(BASIC_TIM_7_CLK,ENABLE);
		  TIM_TimeBaseStructure.TIM_Period = Period;
		  TIM_TimeBaseStructure.TIM_Prescaler = Psc;
		  TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);
			TIM_ClearFlag(TIM7,TIM_FLAG_Update);
      Basic_TIM_Col(Set_DISABLE);
		  TIM_CODE.TIM_Data = TIM7;
		  TIM_CODE.NVIC_CH = TIM7_IRQn;
			break;
	}
}
/*
基本定时器中断服务函数  由用户自己定义
*/
int Basic_TIM_IRQ_Function()
{
		if ( TIM_GetITStatus( TIM6, TIM_IT_Update) != RESET ) 
	{	
		time++;
		TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);  		 
	}
	return 0;
}
/*
基本定时器中断控制函数
void Basic_TIM_NVIC_Config(uint TIM_NUM)
                            BASIC_TIM_6 /7
*/
void Basic_TIM_NVIC_Config(uint TIM_NUM)
{
		NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
	if(TIM_NUM == 1)
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ;	
	if(TIM_NUM == 2)
		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//data resister order to review the set before

