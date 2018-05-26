#include "stm32f10x.h"
#include "SysTick.h"
#include "GPIO_Config.h"
#include "stm32f10x_define.h"


#define uint unsigned int
#define uchar unsigned char

static __IO u32 TimingDelay;


/*
SysTick�û����ƺ��� USERSHEET
SysTick_Col(uint8_t Status)
                   ����״̬
Status Set_ENABLE  ����  Set_DISABLE �ر�
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
SysTick��ʼ������ USERSHEET
SysTick_Init(uint8_t Timeus)
                   �����ж�ʱ��
Timeus΢�뼶   ���������жϵ�ʱ��
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
SysTick�жϷ����� USERSHEET
�û��������
*/
uint8_t SysTick_IRQ_Function()
{
	return 0;
}
/*
����Counter�Ĵ�����ֵUSERSHEET
int Set_Counter(u8 Counter_Val)
                   �Ĵ�����ֵ
Counter_Val  u8  0-65535
ʹ�ý���
ǰ�ᣬʹ����INIT֮��
*/
int Set_Counter(u8 Counter_Val)
{
	SysTick->VAL = Counter_Val;
	return 0;
}


/*
ϵͳ��ʱ����������
Systick_Fast_Set();
�趨10us����һ���ж�
*/
void Systick_Fast_Set()
{
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0???
	{ 
		while (1);
	}
}

/*
ϵͳ��ʱ����ʱ
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
ϵͳ��ʱ����ʱ
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
���Ļ�ȡ����
void TimingDelay_Decrement(void)
*/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}