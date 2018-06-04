#include "stm32f10x.h"
#include "TIM_Config.h"
#include "GPIO_Config.h"
#include "stm32f10x_define.h"
#define uint unsigned int
#define uchar unsigned char

//1MHz = 1000000Hz

extern volatile uint32_t time;

#define BASIC_TIM_CLK_Cmd    RCC_APB1PeriphClockCmd  //������ʱ��ʱ�ӿ��ƺ���
#define GENERAL_TIM_CLK_Cmd  RCC_APB1PeriphClockCmd  //ͨ�ö�ʱ��ʱ�ӿ��ƺ���

float Duty_Set;

typedef struct  
{
  TIM_TypeDef* TIM_Data;
	uint8_t NVIC_CH;
}TIM_INFMATION;

TIM_INFMATION TIM_CODE;
typedef struct
{
	uint16_t PSC_DATA0;
	uint16_t PSC_DATA1;
	uint16_t PSC_DATA2;
	uint16_t PSC_DATA3;
}PSC;

PSC PSCA;//���㲻ͬ��ʱ�����ؼ�������ֵ����֮�����øı估ռ�ձȵļ��㺯��

uint32_t Channel_FLAG;

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
		case 6:
			BASIC_TIM_CLK_Cmd(RCC_APB1Periph_TIM6,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
		  TIM_TimeBaseStructure.TIM_Prescaler = Psc;
		  TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
			TIM_ClearFlag(TIM6,TIM_FLAG_Update);
		  Basic_TIM_Col(Set_DISABLE);
			TIM_CODE.TIM_Data = TIM6;
		  TIM_CODE.NVIC_CH = TIM6_IRQn;
			break;
		case 7:
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
	return 0;
}
/*
������ʱ���жϿ��ƺ���
void Set_TIM_NVIC_Config(uint TIM_NUM)
                            BASIC_TIM_2/6 /7
*/
void Set_TIM_NVIC_Config(uint TIM_NUM)
{
		NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
	if(TIM_NUM == 2)
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;	
	if(TIM_NUM == 3)
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;	
	if(TIM_NUM == 4)
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;	
	if(TIM_NUM == 5)
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ;	
	if(TIM_NUM == 6)
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ;	
	if(TIM_NUM == 7)
		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**********ͨ�ö�ʱ������***********/
/*
	ͨ�ö�ʱ����ʼ������ USERSHEET
void General_TIM_Config(uint8_t TIMx,uint16_t Period,uint16_t,Psc,uint8_t Mode)
                              ��ʱ��          ����        ��Ƶ����     ģʽ
TIMx              TIM2 TIM3 TIM4 TIM5
Period            ��������
Psc               ��Ƶ���ӣ�һ��Ϊ71
Mode              TIM_Mode_Up TIM_Mode_Down 
*/
void General_TIM_Config(uint8_t TIMx,uint16_t Period,uint16_t Psc,uint8_t Mode)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		switch(Mode)
	{
		case 1:
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			break;
		case 2:
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
			break;
	}
	switch(TIMx)
	{
		case 2:
			GENERAL_TIM_CLK_Cmd(RCC_APB1Periph_TIM2,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
			TIM_TimeBaseStructure.TIM_Prescaler = Psc;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_ClearFlag(TIM2, TIM_FLAG_Update);
			TIM_CODE.TIM_Data = TIM2;
			TIM_CODE.NVIC_CH = TIM2_IRQn;
			TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
			break;	
		case 3:
			GENERAL_TIM_CLK_Cmd(RCC_APB1Periph_TIM3,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
			TIM_TimeBaseStructure.TIM_Prescaler = Psc;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
			TIM_CODE.TIM_Data = TIM3;
			TIM_CODE.NVIC_CH = TIM3_IRQn;
			TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
			break;
		case 4:
			GENERAL_TIM_CLK_Cmd(RCC_APB1Periph_TIM4,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
			TIM_TimeBaseStructure.TIM_Prescaler = Psc;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
			TIM_CODE.TIM_Data = TIM4;
			TIM_CODE.NVIC_CH = TIM4_IRQn;
			TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
			break;
		case 5:
			GENERAL_TIM_CLK_Cmd(RCC_APB1Periph_TIM5,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
			TIM_TimeBaseStructure.TIM_Prescaler = Psc;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_ClearFlag(TIM4, TIM_FLAG_Update);
			TIM_CODE.TIM_Data = TIM5;
			TIM_CODE.NVIC_CH = TIM5_IRQn;
			TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
			break;
	}
	Basic_TIM_Col(Set_DISABLE);
}

/*
ͨ�ö�ʱ���жϿ��ƺ���
void GENERAL_TIM_Mode_Config(void)
*/

/*******************************************/
/************ͨ�ö�ʱ��FTMģ��ʹ************/
/*FTM���ͨ���ĸ�д��stm32f10x_define.h*/
/*******************************************/
/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)
/*
#define            GENERAL_TIM_Period            99
#define            GENERAL_TIM_Prescaler         71
*/
/*******************************************/
/*
FTMģ���ʼ������
FTM_INIT(uint FTMx,uint Channel,uint Frequance,double Duty)
FTMx           FTM0~FTM3
Channel        FTM0_CH1.........
frequance      ��λHz
Duty           0.1 0.2 0.36  .....
*/
void FTM_INIT(uint FTMx,uint Channel,uint Frequance,double Duty)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t GENERAL_TIM_Period;
	float CCR_Val;
	uint16_t PSC_CAL;
	uint16_t Period_CAL;
	
	Duty_Set = Duty;
	PSC_CAL = GENERAL_TIM_Prescaler+1;
	GENERAL_TIM_Period = 72000000/(Frequance*PSC_CAL);  //ARR
	Period_CAL = GENERAL_TIM_Period+1;
	/***************��Ҫ�û��Լ�����**********************/
	CCR_Val = (Duty)*Period_CAL;																//CRR
	/*****************************************************/
	switch(FTMx)
	{
		case 0:  //FTM0
			PSCA.PSC_DATA0 = Period_CAL;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	

					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);				
								
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC1Init(TIM2, &TIM_OCInitStructure);
					TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM2, ENABLE);
					break;
					
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);		
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
				
					// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC2Init(TIM2, &TIM_OCInitStructure);
					TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM2, ENABLE);
					break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	
				
// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC3Init(TIM2, &TIM_OCInitStructure);
					TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM2, ENABLE);
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);			
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
				
// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC4Init(TIM2, &TIM_OCInitStructure);
					TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM2, ENABLE);
					break;
			}
			break;
		case 1:   //FTM1
			PSCA.PSC_DATA1 = Period_CAL;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC1Init(TIM5, &TIM_OCInitStructure);
					TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM5, ENABLE);
				
					break;
				case 2:
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC2Init(TIM5, &TIM_OCInitStructure);
					TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM5, ENABLE);					
					break;
				case 3:
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC3Init(TIM5, &TIM_OCInitStructure);
					TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM5, ENABLE);
					break;
				case 4:
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC4Init(TIM5, &TIM_OCInitStructure);
					TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM5, ENABLE);				
					break;
			}			
			break;
		case 2:  //FTM2
			PSCA.PSC_DATA2 = Period_CAL;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC1Init(TIM3, &TIM_OCInitStructure);
					TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM3, ENABLE);					
					break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC2Init(TIM3, &TIM_OCInitStructure);
					TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM3, ENABLE);						
					break;
				case 3:
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC3Init(TIM3, &TIM_OCInitStructure);
					TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM3, ENABLE);						
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC4Init(TIM3, &TIM_OCInitStructure);
					TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM3, ENABLE);						
					break;
			}			
			break;
		case 3:   //FTM3
			PSCA.PSC_DATA3 = Period_CAL;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC1Init(TIM4, &TIM_OCInitStructure);
					TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM4, ENABLE);	
					break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC2Init(TIM4, &TIM_OCInitStructure);
					TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM4, ENABLE);						
					break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC3Init(TIM4, &TIM_OCInitStructure);
					TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM4, ENABLE);						
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		
			
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// ����ΪPWMģʽ1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC4Init(TIM4, &TIM_OCInitStructure);
					TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM4, ENABLE);	
					break;
			}			
			break;
	}
	
}
/*
FTM���ƺ���
ע��һ�㲻�ã�Ҫ���Ƽ�����������ֹͣ��ʱ������
void FTM_COL(TIM_TypeDef* FTMx,FunctionalState NewState)
FTMx  FTM0~3
NewState ENABLE DISABLE
*/
void FTM_COL(TIM_TypeDef* FTMx,FunctionalState NewState)
{
		TIM_Cmd(FTMx, NewState);
}

/*
����ռ�ձȺ���
void Set_Duty(uint FTMx,uint16_t channel,double duty)
FTMx  FTM0~3
channel  FTM0_CH1.......
duty	 0.1  0.2  0.63  0.15.......								
*/
void Set_Duty(uint FTMx,uint16_t channel,double duty)
{
	uint16_t Duty;
	switch(FTMx)
	{
		case 0:
			//FTM0
		Duty = duty*PSCA.PSC_DATA0;
	switch(channel)
	{
		case 1:
			TIM_SetCompare1(TIM2,Duty);
			break;
		case 2:
			TIM_SetCompare2(TIM2,Duty);
			break;
		case 3:
			TIM_SetCompare3(TIM2,Duty);
			break;
		case 4:
			TIM_SetCompare4(TIM2,Duty);
			break;
	}
	break;
	case 1:
		//FTM1
	Duty = duty*PSCA.PSC_DATA1;
	switch(channel)
	{
		case 1:
			TIM_SetCompare1(TIM5,Duty);
			break;
		case 2:
			TIM_SetCompare2(TIM5,Duty);
			break;
		case 3:
			TIM_SetCompare3(TIM5,Duty);
			break;
		case 4:
			TIM_SetCompare4(TIM5,Duty);
			break;
	}
	break;
	case 2:
				//FTM2
	Duty = duty*PSCA.PSC_DATA2;
	switch(channel)
	{
		case 1:
			TIM_SetCompare1(TIM3,Duty);
			break;
		case 2:
			TIM_SetCompare2(TIM3,Duty);
			break;
		case 3:
			TIM_SetCompare3(TIM3,Duty);
			break;
		case 4:
			TIM_SetCompare4(TIM3,Duty);
			break;
	}
	break;
	case 3:
				//FTM3
	Duty = duty*PSCA.PSC_DATA3;
	switch(channel)
	{
		case 1:
			TIM_SetCompare1(TIM4,Duty);
			break;
		case 2:
			TIM_SetCompare2(TIM4,Duty);
			break;
		case 3:
			TIM_SetCompare3(TIM4,Duty);
			break;
		case 4:
			TIM_SetCompare4(TIM4,Duty);
			break;
	}
	break;
}
}
//data resister order to review the set before

