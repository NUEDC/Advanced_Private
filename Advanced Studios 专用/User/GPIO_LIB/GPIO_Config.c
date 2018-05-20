#include "GPIO_Config.h"
#include "stm32f10x.h"
#define uint unsigned int



//特殊数据结构

//data resister order to review the set before
typedef struct  
{
	char GPIO_PORT;       //引脚Port单独定义
	uint16_t GPIO_PIN;    //引脚Pin
	GPIOSpeed_TypeDef GPIO_Speed;  //引脚速度
	GPIOMode_TypeDef GPIO_Mode;  //引脚模式
	
}GPIO_CFG;

//参数定义

extern GPIO_CFG GPIO_CONFIG;


/*
	GPIO初始化函数 USER SHEET
	int GPIO_INIT(uint port,uint16_t pin,uint8_t Speed,uint8_t mode,uint8_t CLK)
                   端口         引脚          速度         模式       时钟线
//端口号  1 GPIOA   2 GPIOB  3  GPIOC  4  GPIOD  5  GPIOE   6  GPIOF  7  GPIOG
//引脚号  0  pin0   1 pin1    2  pin2   ~~~~~~~~~~    15  pin15
//速度    2  2MHz   10 10MHz    50 50MHz
//模式    1  模拟输入  2  浮空输入  3  下拉输入    4  上拉输出   5  开漏输出   6  推挽输出   7  复用开漏输出  8  复用推挽输出
//时钟线 (RCC_APB2Periph)  1 GPIOA   2 GPIOB  3  GPIOC  4  GPIOD  5  GPIOE   6  GPIOF  7  GPIOG

*/
int GPIO_INIT(uint port,uint16_t pin,uint8_t Speed,uint8_t mode,uint8_t CLK)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   //Define a struct about gpio init
	
	switch(pin)
	{
		case 1:   
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
		  GPIO_CONFIG.GPIO_PIN = GPIO_Pin_1;
			break;
		case 2:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
		  GPIO_CONFIG.GPIO_PIN = GPIO_Pin_2;
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; 
		  GPIO_CONFIG.GPIO_PIN = GPIO_Pin_3;
			break;
		case 4:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; 
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_4;
			break;
		case 5:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ; 
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_5;
			break;
		case 6:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; 
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_6;
			break;
	  case 7:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; 
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_7;
			break;
		case 8:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_8;
			break;
		case 9:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_9;
			break;
		case 10:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ; 
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_10;
			break;
		case 11:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_11;
			break;
		case 12:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; 
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_12;
			break;
		case 13:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_13;
			break;
		case 14:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_14;
			break;
		case 15:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_15;
			break;
	  case 0:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
			GPIO_CONFIG.GPIO_PIN = GPIO_Pin_0;
			break;
	};
	
	switch(Speed)
	{
			case 10:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz ;
			GPIO_CONFIG.GPIO_Speed = GPIO_Speed_10MHz;
			break;
			case 2:
			GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz ;
			GPIO_CONFIG.GPIO_Speed = GPIO_Speed_2MHz;
			break;
			case 50:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
			GPIO_CONFIG.GPIO_Speed = GPIO_Speed_50MHz;
			break;
	};	
	
	switch(mode)
	{
			case 1:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;// 模拟输入
			GPIO_CONFIG.GPIO_Mode = GPIO_Mode_AIN;
			break;
			case 2:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;// 浮空输入
			GPIO_CONFIG.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			break;
			case 3:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;// 下拉输入
			GPIO_CONFIG.GPIO_Mode = GPIO_Mode_Out_OD;
			break;
			case 4:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;	// 上拉输入
			GPIO_CONFIG.GPIO_Mode = GPIO_Mode_IPU;
			break;
			case 5:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;	// 开漏输出
			GPIO_CONFIG.GPIO_Mode = GPIO_Mode_Out_OD;
			break;
			case 6:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;// 推挽输出
			GPIO_CONFIG.GPIO_Mode = GPIO_Mode_Out_PP;
			break;
			case 7:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;// 复用开漏输出
			GPIO_CONFIG.GPIO_Mode = GPIO_Mode_AF_OD;
			break;
			case 8:
			GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_AF_PP;// 复用推挽输出
			GPIO_CONFIG.GPIO_Mode = GPIO_Mode_AF_PP;
			break;
		};
  switch(CLK)
	{
		case 1:   
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		
			break;
		case 2:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
			break;
		case 3:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
			break;
		case 4:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); 
			break;
		case 5:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE); 
			break;
		case 6:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);  
			break;
	  case 7:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE); 
			break;
	};
  switch(port)
	{
		case 1:
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_CONFIG.GPIO_PORT = (char)'A';
		break;
		case 2:
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			GPIO_CONFIG.GPIO_PORT = (char)'B';		
		break;
		case 3:
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			GPIO_CONFIG.GPIO_PORT = (char)'C';
		break;
		case 4:
			GPIO_Init(GPIOD, &GPIO_InitStructure);	
			GPIO_CONFIG.GPIO_PORT = (char)'D';
		break;
		case 5:
			GPIO_Init(GPIOE, &GPIO_InitStructure);	
			GPIO_CONFIG.GPIO_PORT = (char)'E';
		break;
		case 6:
			GPIO_Init(GPIOF, &GPIO_InitStructure);	
			GPIO_CONFIG.GPIO_PORT = (char)'F';
		break;
		case 7:
			GPIO_Init(GPIOG, &GPIO_InitStructure);	
			GPIO_CONFIG.GPIO_PORT = (char)'G';
		break;
	};
	return 0;
}
