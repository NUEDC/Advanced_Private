#include "stm32f10x.h"
#include "GPIO_Config.h"
#include "stm32f10x_define.h"
#define uint unsigned int
	
/*�����ϸ�ڶ����stm32f10x_define.h*/


//data resister order to review the set before

GPIO_CFG GPIO_CON;
/*
	GPIO��ʼ������ USER SHEET
	int GPIO_INIT(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t Speed,uint8_t mode,uint8_t CLK)
                            �˿�         ����          �ٶ�         ģʽ       ʱ����
//�˿ں�  GPIOx  GPIOA GPIOB ~~~
//���ź�   pin0  GPIO_Pin_0   pin1  GPIO_Pin_1  pin2  GPIO_Pin_2  ~~~~~~    pin15  GPIO_Pin_15
//ģʽ    1  ģ������  2  ��������  3  ��������    4  �������   5  ��©���   6  �������   7  ���ÿ�©���  8  �����������
//�ٶ�    LOW_Speed                    2MHz
          MID_Speed                   10MHz
          HIGH_Speed                  50MHz
*/
extern int GPIO_INIT(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t Speed,uint8_t mode)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   //Define a struct about gpio init
	
	switch(pin)
	{
		case 1:   
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
		  GPIO_CON.GPIO_PIN = GPIO_Pin_1;
			break;
		case 2:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
		  GPIO_CON.GPIO_PIN = GPIO_Pin_2;
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; 
		  GPIO_CON.GPIO_PIN = GPIO_Pin_3;
			break;
		case 4:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_4;
			break;
		case 5:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_5;
			break;
		case 6:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_6;
			break;
	  case 7:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_7;
			break;
		case 8:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_8;
			break;
		case 9:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_9;
			break;
		case 10:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_10;
			break;
		case 11:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_11;
			break;
		case 12:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_12;
			break;
		case 13:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
			GPIO_CON.GPIO_PIN = GPIO_Pin_13;
			break;
		case 14:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
			GPIO_CON.GPIO_PIN = GPIO_Pin_14;
			break;
		case 15:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
			GPIO_CON.GPIO_PIN = GPIO_Pin_15;
			break;
	  case 0:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
			GPIO_CON.GPIO_PIN = GPIO_Pin_0;
			break;
	};
	
	switch(Speed)
	{
			case 10:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_10MHz;
			break;
			case 2:
			GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_2MHz;
			break;
			case 50:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_50MHz;
			break;
	};	
	
	switch(mode)
	{
			case 1:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;// ģ������
			GPIO_CON.GPIO_Mode = GPIO_Mode_AIN;
			break;
			case 2:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;// ��������
			GPIO_CON.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			break;
			case 3:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;// ��������
			GPIO_CON.GPIO_Mode = GPIO_Mode_Out_OD;
			break;
			case 4:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;	// ��������
			GPIO_CON.GPIO_Mode = GPIO_Mode_IPU;
			break;
			case 5:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;	// ��©���
			GPIO_CON.GPIO_Mode = GPIO_Mode_Out_OD;
			break;
			case 6:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;// �������
			GPIO_CON.GPIO_Mode = GPIO_Mode_Out_PP;
			break;
			case 7:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;// ���ÿ�©���
			GPIO_CON.GPIO_Mode = GPIO_Mode_AF_OD;
			break;
			case 8:
			GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_AF_PP;// �����������
			GPIO_CON.GPIO_Mode = GPIO_Mode_AF_PP;
			break;
		};
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);
	return 0;
	 
 }
 /*
PORT���������ʼ������ USER SHEET
 int Fast_OutputSet(GPIO_TypeDef* GPIOx,uint pin)
                         �˿�          ����
//�˿ں� GPIOx  GPIOA GPIOB ~~~
//���ź�  pin0  GPIO_Pin_0   pin1  GPIO_Pin_1  pin2  GPIO_Pin_2  ~~~~~~    pin15  GPIO_Pin_15
//��������Ϊ50MHz����
*/
int Fast_OutputSet(GPIO_TypeDef* GPIOx,uint pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //Define a struct about gpio init
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	switch(pin)
	{
		case 1:   
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
			break;
		case 2:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; 
			break;
		case 4:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; 
			break;
		case 5:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ; 
			break;
		case 6:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; 
			break;
	  case 7:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; 
			break;
		case 8:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
			break;
		case 9:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
			break;
		case 10:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ; 
			break;
		case 11:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
			break;
		case 12:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; 
			break;
		case 13:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
			break;
		case 14:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
			break;
		case 15:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
			break;
	  case 0:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
			break;
	};
	GPIO_Init(GPIOx, &GPIO_InitStructure);
	
	return 0;
}
 /*
PORT���������ʼ������ USER SHEET
Fast_InputSet(GPIO_TypeDef* GPIOx,uint pin,uint Speed)
                           �˿�      ����      �ٶ�
//�˿ں�  GPIOx  GPIOA GPIOB ~~~
//���ź�  pin0  GPIO_Pin_0   pin1  GPIO_Pin_1  pin2  GPIO_Pin_2  ~~~~~~    pin15  GPIO_Pin_15
//�ٶ�    LOW_Speed                    2MHz
          MID_Speed                   10MHz
          HIGH_Speed                  50MHz
*/
int Fast_InputSet(GPIO_TypeDef* GPIOx,uint pin,uint Speed)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //Define a struct about gpio init
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
		 switch(Speed)
	{
			case 10:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_10MHz;
			break;
			case 2:
			GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_2MHz;
			break;
			case 50:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_50MHz;
			break;
	};
		switch(pin)
	{
		case 1:   
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
			break;
		case 2:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; 
			break;
		case 4:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; 
			break;
		case 5:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ; 
			break;
		case 6:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; 
			break;
	  case 7:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; 
			break;
		case 8:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
			break;
		case 9:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
			break;
		case 10:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ; 
			break;
		case 11:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
			break;
		case 12:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; 
			break;
		case 13:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
			break;
		case 14:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
			break;
		case 15:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
			break;
	  case 0:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
			break;
	};
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);
	return 0;
}
 /*
PORT���������ʼ������ USER SHEET
Change_Port_Mode(GPIO_TypeDef* GPIOx,uint pin,uint mode,uint Speed)
                             �˿�      ����       ģʽ        �ٶ�
//�˿ں�  GPIOx  GPIOA GPIOB ~~~
//���ź�  pin0  GPIO_Pin_0   pin1  GPIO_Pin_1  pin2  GPIO_Pin_2  ~~~~~~    pin15  GPIO_Pin_15
//�ٶ�    LOW_Speed                    2MHz
          MID_Speed                   10MHz
          HIGH_Speed                  50MHz
//ģʽ  1  ģ������  2  ��������  3  ��������    4  �������   5  ��©���   6  �������   7  ���ÿ�©���  8  �����������
*/
int Change_Port_Mode(GPIO_TypeDef* GPIOx,uint pin,uint mode,uint Speed)
{
  GPIO_INIT(GPIOx,pin,Speed,mode);
}
 /*
�˿ھ�Ĭ���� �Ͽ��˿�ʱ�� USER SHEET
Cut_PIN_CLK(uint port)
               �˿�            
//�˿ں�  GPIOA_SET GPIOA   GPIOB_SET GPIOB  GPIOC_SET  GPIOC  GPIOD_SET  GPIOD  GPIOE_SET  GPIOE   GPIOF_SET  GPIOF  GPIOG_SET  GPIOG
*/
int Cut_PIN_CLK(uint port)
{
	switch(port)
	{
		case 1:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,ENABLE);
			break;
		case 2:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB,ENABLE);
			break;
		case 3:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC,ENABLE);
			break;
		case 4:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD,ENABLE);
			break;
		case 5:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE,ENABLE);
			break;
		case 6:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF,ENABLE);
			break;
		case 7:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG,ENABLE);
			break;
	};
	return 0;
}
 /*
����˿ھ�Ĭ���� �����˿�ʱ�� USER SHEET
Reconnect_PIN_CLK(uint port)
                   �˿�            
//�˿ں�  GPIOA_SET GPIOA   GPIOB_SET GPIOB  GPIOC_SET  GPIOC  GPIOD_SET  GPIOD  GPIOE_SET  GPIOE   GPIOF_SET  GPIOF  GPIOG_SET  GPIOG
//ʹ���Ⱦ����� ���� Cut_PIN_CLK(uint port) ֮��
*/
int Reconnect_PIN_CLK(uint port)
{
		switch(port)
	{
		case 1:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,DISABLE);
			break;
		case 2:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB,DISABLE);
			break;
		case 3:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC,DISABLE);
			break;
		case 4:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD,DISABLE);
			break;
		case 5:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE,DISABLE);
			break;
		case 6:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF,DISABLE);
			break;
		case 7:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG,DISABLE);
			break;
	};
	return 0;
}
 /*
����ߵ͵�ƽ���� USER SHEET
GPIO_OUT(uint port,uint pin,uint data)
              �˿�     ����    �ߵ͵�ƽ   
//�˿ں�  port  GPIOA\GPIOB\GPIOC\GPIOD~~
//���ź�  pin  GPIO_Pin_0 GPIO_Pin_1 GPIO_Pin_2 GPIO_Pin_3~~~
//�ߵ͵�ƽ (data) Bit_SET 1;Bit_RESET 0;
//ʹ���Ⱦ����� ���ó�ʼ���˿�֮��
*/
int GPIO_OUT(GPIO_TypeDef* port,uint16_t pin,BitAction data)
{
GPIO_WriteBit(port,pin, data);
	return 0;
}
 /*
��ȡ����ߵ͵�ƽ���� USER SHEET
GPIO_READ(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
                 �˿�              ����      
//�˿ں�  GPIOx  GPIOA\GPIOB\GPIOC\GPIOD~~
//���ź�  GPIO_Pin  GPIO_Pin_0 GPIO_Pin_1 GPIO_Pin_2 GPIO_Pin_3~~~
//ʹ���Ⱦ����� ���ó�ʼ���˿�֮��
*/
uint8_t GPIO_READ(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{
	uint8_t Read_data;
	Read_data = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	return Read_data;
}
 /*
�˿����������(����Ϊ16����) USER SHEET
GPIO_Write_Port(GPIO_TypeDef* GPIOx,u16 Val)
                      �˿�          ���ֵ
//�˿ں�  GPIOx  GPIOA\GPIOB\GPIOC\GPIOD~~
//���ֵ  Val  0x02~~
//ʹ���Ⱦ����� ���ó�ʼ���˿�֮��
*/
void GPIO_Write_Port(GPIO_TypeDef* GPIOx,u16 Val)
{
	GPIO_Write(GPIOx,Val);
}
 /*
��ȡ�˿�����(16λ) USER SHEET
GPIO_Read_Port(GPIO_TypeDef* GPIOx)
                      �˿�         
//�˿ں�  GPIOx  GPIOA\GPIOB\GPIOC\GPIOD~~
//ʹ���Ⱦ����� ���ó�ʼ���˿�֮��
*/
u16 GPIO_Read_Port(GPIO_TypeDef* GPIOx)
{
	u16 Read_Val;
	Read_Val = GPIO_ReadInputData(GPIOx);
	return Read_Val;
}
 /**/ 