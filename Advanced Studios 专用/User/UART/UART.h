#ifdef __UART_H__
#define __UART_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#define uint unsigned int
#define uchar unsigned char
	

//��������

//���ر�������
extern int UART_CONFIG(uint UARTx,uint BaudRate,uint Word_Length,uint Stop_Bits,uint Parity); //USART��ʼ��
extern void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch); //����һ���ֽ�
extern void Usart_SendString( USART_TypeDef * pUSARTx, char *str);  //�����ַ���
extern void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);  //����һ��16λ��
extern void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num); //����8λ����
extern int fputc(int ch, FILE *f);//�ض���printf
extern int fgetc(FILE *f);//�ض���scanf


#endif
	
