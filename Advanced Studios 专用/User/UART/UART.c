#include "stm32f10x.h"
#include "UART.h"
#include "stm32f10x_define.h"
#include <stdio.h>

#define uint unsigned int
#define uchar unsigned char


typedef struct  
{
 USART_TypeDef * pUSARTx;
}Connect;

Connect P_S_function;

/*
重定向C库函数 USER SHEET
void set_P_S_VECTOR(USART_TypeDef * pUSARTx)
																		串口
pUSARTx USART1 USART2 USART3 UART4 UART5
*/

void set_P_S_VECTOR(USART_TypeDef * pUSARTx)
{
	P_S_function.pUSARTx=pUSARTx;
}
/*
	串口初始化函数 USER SHEET
  UART_CONFIG(uint UARTx,uint BaudRate,uint Word_Length,uint Stop_Bits,uint Parity)
                   串口号      比特率        字长             停止位        校验位
  UARTx UART1_SET  UART2_SET  UART3_SET  UART4_SET  UART5_SET
  BaudRate  9600 115200 25600...
  Word Length 8,9
  Stop_Bits   1,2
  Parity      1 Odd  2  EVEN  0 NO
*/
int UART_CONFIG(uint UARTx,uint BaudRate,uint Word_Length,uint Stop_Bits,uint Parity)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	switch(UARTx)
	{
		case 1:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = BaudRate;
		if(Word_Length == 8)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		}
		if(Word_Length == 9)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_9b;
		}
		if(Stop_Bits == 1)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		}
		if(Stop_Bits == 2)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_2;
		}
		if(Parity == 1)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Odd;
		}
		if(Parity == 2)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Even;
		}
	  if(Parity == 0)
		{
			USART_InitStructure.USART_Parity = USART_Parity_No;
		}
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1, ENABLE);
		break;
		
		case 2:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = BaudRate;
		if(Word_Length == 8)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		}
		if(Word_Length == 9)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_9b;
		}
		if(Stop_Bits == 1)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		}
		if(Stop_Bits == 2)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_2;
		}
		if(Parity == 1)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Odd;
		}
		if(Parity == 2)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Even;
		}
	  if(Parity == 0)
		{
			USART_InitStructure.USART_Parity = USART_Parity_No;
		}
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART2, &USART_InitStructure);
		USART_Cmd(USART2, ENABLE);
		break;
		
	case 3:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = BaudRate;
		if(Word_Length == 8)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		}
		if(Word_Length == 9)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_9b;
		}
		if(Stop_Bits == 1)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		}
		if(Stop_Bits == 2)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_2;
		}
		if(Parity == 1)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Odd;
		}
		if(Parity == 2)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Even;
		}
	  if(Parity == 0)
		{
			USART_InitStructure.USART_Parity = USART_Parity_No;
		}
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART3, &USART_InitStructure);
		USART_Cmd(USART3, ENABLE);
		break;
	case 4:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = BaudRate;
		if(Word_Length == 8)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		}
		if(Word_Length == 9)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_9b;
		}
		if(Stop_Bits == 1)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		}
		if(Stop_Bits == 2)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_2;
		}
		if(Parity == 1)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Odd;
		}
		if(Parity == 2)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Even;
		}
	  if(Parity == 0)
		{
			USART_InitStructure.USART_Parity = USART_Parity_No;
		}
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(UART4, &USART_InitStructure);
		USART_Cmd(UART4, ENABLE);
		break;
		
	case 5:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = BaudRate;
		if(Word_Length == 8)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		}
		if(Word_Length == 9)
		{
		USART_InitStructure.USART_WordLength = USART_WordLength_9b;
		}
		if(Stop_Bits == 1)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		}
		if(Stop_Bits == 2)
		{
		USART_InitStructure.USART_StopBits = USART_StopBits_2;
		}
		if(Parity == 1)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Odd;
		}
		if(Parity == 2)
		{
			USART_InitStructure.USART_Parity = USART_Parity_Even;
		}
	  if(Parity == 0)
		{
			USART_InitStructure.USART_Parity = USART_Parity_No;
		}
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(UART5, &USART_InitStructure);
		USART_Cmd(UART5, ENABLE);
		break;
	}
	return 0;
}
/*
	串口发送一个字节 USER SHEET
  Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
                                串口号          内容
  UARTx USART1  USART2  USART3T  UART4  UART5
  ch    内容
*/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*
	串口发送一个8位数组 USER SHEET
  Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
                                   串口号          数组        内容个数
  UARTx USART1  USART2  USART3T  UART4  UART5
*/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}
/*
	串口发送字符串 USER SHEET
 Usart_SendString( USART_TypeDef * pUSARTx, char *str)
                                   串口号       内容    
  UARTx USART1  USART2  USART3T  UART4  UART5
*/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}
/*
	串口发送16位数 USER SHEET
 Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
                                    串口号        内容    
  UARTx USART1  USART2  USART3T  UART4  UART5
*/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}




//重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(P_S_function.pUSARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(P_S_function.pUSARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(P_S_function.pUSARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(P_S_function.pUSARTx);
}
/*
快速UART设置   默认配置：波特率115200，字长8，不进行校验，停止位1
Fast_UART_SET(uint UARTx)
                              串口
UARTx  UART1_SET UART2_SET UART3_SET UART4_SET UART5_SET
*/
void Fast_UART_SET(uint UARTx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	switch(UARTx)
	{
		case 1:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1, ENABLE);
		break;
		
		case 2:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART2, &USART_InitStructure);
		USART_Cmd(USART2, ENABLE);
		break;
		
	case 3:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART3, &USART_InitStructure);
		USART_Cmd(USART3, ENABLE);
		break;
	case 4:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(UART4, &USART_InitStructure);
		USART_Cmd(UART4, ENABLE);
		break;
		
	case 5:
			
		//配置UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
    //配置UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
		//配置输入输出数据
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(UART5, &USART_InitStructure);
		USART_Cmd(UART5, ENABLE);
		break;
	}
}