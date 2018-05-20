#ifdef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__
#include "stm32f10x.h"

#define uint unsigned int
#define uchar unsigned char
	
//特殊定义

//返回变量声明

extern GPIO_CFG GPIO_CONFIG;

//函数声明
extern int GPIO_INIT(uint port,uint16_t pin,uint8_t speed,uint8_t mode,uint8_t CLK);  //GPIO模式初始化函数

#endif
