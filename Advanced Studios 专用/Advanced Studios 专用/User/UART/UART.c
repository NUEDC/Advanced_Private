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
�ض���C�⺯�� USER SHEET
void set_P_S_VECTOR(USART_TypeDef * pUSARTx)
																		����
pUSARTx USART1 USART2 USART3 UART4 UART5
*/

void set_P_S_VECTOR(USART_TypeDef * pUSARTx)
{
	P_S_function.pUSARTx=pUSARTx;
}
/*
	���ڳ�ʼ������ USER SHEET
  UART_CONFIG(uint UARTx,uint BaudRate,uint Word_Length,uint Stop_Bits,uint Parity)
                   ���ں�      ������        �ֳ�             ֹͣλ        У��λ
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
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		//���������������
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
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		//���������������
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
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
		//���������������
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
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
		//���������������
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
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
		//���������������
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
	���ڷ���һ���ֽ� USER SHEET
  Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
                                ���ں�          ����
  UARTx USART1  USART2  USART3T  UART4  UART5
  ch    ����
*/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*
	���ڷ���һ��8λ���� USER SHEET
  Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
                                   ���ں�          ����        ���ݸ���
  UARTx USART1  USART2  USART3T  UART4  UART5
*/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}
/*
	���ڷ����ַ��� USER SHEET
 Usart_SendString( USART_TypeDef * pUSARTx, char *str)
                                   ���ں�       ����    
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
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}
/*
	���ڷ���16λ�� USER SHEET
 Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
                                    ���ں�        ����    
  UARTx USART1  USART2  USART3T  UART4  UART5
*/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}




//�ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(P_S_function.pUSARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(P_S_function.pUSARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(P_S_function.pUSARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(P_S_function.pUSARTx);
}
/*
����UART����   Ĭ�����ã�������115200���ֳ�8��������У�飬ֹͣλ1
Fast_UART_SET(uint UARTx)
                              ����
UARTx  UART1_SET UART2_SET UART3_SET UART4_SET UART5_SET
*/
void Fast_UART_SET(uint UARTx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	switch(UARTx)
	{
		case 1:
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		//���������������
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
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		//���������������
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
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
		//���������������
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
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
		//���������������
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
			
		//����UART1  TX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
    //����UART1  RX
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
		//���������������
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