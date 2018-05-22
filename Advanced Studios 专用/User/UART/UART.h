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
	

//参数定义

//返回变量声明
extern int UART_CONFIG(uint UARTx,uint BaudRate,uint Word_Length,uint Stop_Bits,uint Parity); //USART初始化
extern void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch); //发送一个字节
extern void Usart_SendString( USART_TypeDef * pUSARTx, char *str);  //发送字符串
extern void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);  //发送一个16位数
extern void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num); //发送8位数组
extern int fputc(int ch, FILE *f);//重定义printf
extern int fgetc(FILE *f);//重定义scanf


#endif
	
