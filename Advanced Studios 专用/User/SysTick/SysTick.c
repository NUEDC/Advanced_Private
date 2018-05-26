#include "stm32f10x.h"
#include "SysTick.h"
#include "GPIO_Config.h"
#include "stm32f10x_define.h"


#define uint unsigned int
#define uchar unsigned char

static __IO u32 TimingDelay;


/*
SysTick用户控制函数 USERSHEET
SysTick_Col(uint8_t Status)
                   控制状态
Status Set_ENABLE  开启  Set_DISABLE 关闭
*/

int SysTick_Col(uint8_t Status)
{
	switch(Status)
	{
		case 1:
			SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
			break;
		case 0:
			SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
			break;
	}
}
/*
SysTick初始化函数 USERSHEET
SysTick_Init(uint8_t Timeus)
                   跳入中断时间
Timeus微秒级   设置跳入中断的时间
*/
int SysTick_Init(uint8_t Timeus)
{
	uint32_t Time;
	Time = (SystemCoreClock/100000)*Timeus;
	SysTick_Config(Time);
	SysTick_Col(Set_DISABLE);
	return 0;
}
/*
SysTick中断服务函数 USERSHEET
用户自行添加
*/
uint8_t SysTick_IRQ_Function()
{
	return 0;
}
/*
设置Counter寄存器初值USERSHEET
int Set_Counter(u8 Counter_Val)
                   寄存器初值
Counter_Val  u8  0-65535
使用较少
前提，使用了INIT之后
*/
int Set_Counter(u8 Counter_Val)
{
	SysTick->VAL = Counter_Val;
	return 0;
}


/*
系统定时器快速设置
Systick_Fast_Set();
设定10us进入一次中断
*/
void Systick_Fast_Set()
{
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0???
	{ 
		while (1);
	}
}

/*
系统定时器延时
Systick_Delay_us(__IO uint32_t us);
*/
void Systick_Delay_us(__IO uint32_t us)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);
	for(i=0;i<us;i++)
	{
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}
/*
系统定时器延时
void Systick_Delay_ms(__IO uint32_t ms)
*/
void Systick_Delay_ms(__IO uint32_t ms)
{
	uint32_t i;	
	SysTick_Config(SystemCoreClock/1000);
	for(i=0;i<ms;i++)
	{
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

/*
节拍获取程序
void TimingDelay_Decrement(void)
*/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}