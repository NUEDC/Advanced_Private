#include "stm32f10x.h"
#include "TIM_Config.h"
#include "GPIO_Config.h"
#include "stm32f10x_define.h"
#define uint unsigned int

extern volatile uint32_t time;

#define BASIC_TIM_CLK_Cmd    RCC_APB1PeriphClockCmd  //������ʱ��ʱ�ӿ��ƺ���


typedef struct  
{
  TIM_TypeDef* TIM_Data;
	uint8_t NVIC_CH;
}TIM_INFMATION;

TIM_INFMATION TIM_CODE;



/*�����ϸ�ڶ����stm32f10x_define.h*/

/*
��ʱ��״̬���ƺ������Կ����͹ر�
 void Basic_TIM_Col(uint8_t Status)
                           ״̬
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


/******������ʱ������******/
/*
������ʱ��TIM6&TIM7��ʼ������
Basic_TIM_Config(uint8_t TIMx,uint8_t Period, uint8_t Psc)
                      TIM        ��ʱ������       ��Ƶ����
  TIMx   BASIC_TIM_6  BASIC_TIM_7
  Period  ����õ� ���Psc=71 ʱ�� 1MHz  Period = 1000 ʱΪ��������1ms
  Psc   һ��Ϊ71�� ϵͳʱ��-1
ע�⣺�κ���û�п�����ʱ���������ǳ�ʼ������Ҫ�ٴ�Enable
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
������ʱ���жϷ�����  ���û��Լ�����
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
������ʱ���жϿ��ƺ���
void Basic_TIM_NVIC_Config(uint TIM_NUM)
                            BASIC_TIM_6 /7
*/
void Basic_TIM_NVIC_Config(uint TIM_NUM)
{
		NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
	if(TIM_NUM == 1)
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ;	
	if(TIM_NUM == 2)
		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//data resister order to review the set before

