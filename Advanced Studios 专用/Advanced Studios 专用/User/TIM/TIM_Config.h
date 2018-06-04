#ifdef __TIM_CONFIG_H__
#define __TIM_CONFIG_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#define uint unsigned int
#define uchar unsigned char
	

//��������

#define BASIC_TIM_CLK_Cmd    RCC_APB1PeriphClockCmd  //������ʱ��ʱ�ӿ��ƺ���


//���ر�������
/***********ͨ�ú���**********************/

/************������ʱ�� TIM6&TIM7**********/
/*ʹ�ó�ʼ��Ҫ��ʼ��NVIC��TIMһ��*/
extern void Basic_TIM_Config(uint8_t TIMx,uint16_t Period, uint16_t Psc);      //������ʱ����ʼ��
extern void Basic_TIM_NVIC_Config(uint TIM_NUM); //������ʱ���ж����ú���
extern int Basic_TIM_IRQ_Function();//������ʱ���жϷ�����
extern void Basic_TIM_Col(uint8_t Status);         //������ʱ�����ƺ���

/************ͨ�ö�ʱ�� TIM2~TIM5**********/
/*ͨ�ö�ʱ���ڱ�����һ��������PWM�źŷ�����*/
extern void General_TIM_Config(uint8_t TIMx,uint16_t Period,uint16_t,Psc,uint8_t Mode); //ͨ�ö�ʱ����ʼ��
/*FTMģ��*/
extern void FTM_INIT(uint FTMx,uint Channel,uint Frequance,double Duty);	  	//FTM��ʼ������
extern void FTM_COL(TIM_TypeDef* FTMx,FunctionalState NewState);  			  		//FTM���ƺ���
extern void Set_Duty(uint FTMx,uint16_t channel,double duty);     				  	//ռ�ձȸ��ĺ���
/************�߼���ʱ�� TIM1&TIM8**********/




//��������

#endif
