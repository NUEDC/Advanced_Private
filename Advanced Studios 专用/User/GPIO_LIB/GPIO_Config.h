#ifdef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#define uint unsigned int
#define uchar unsigned char
	

//��������

//���ر�������


//��������
extern int GPIO_INIT(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t Speed,uint8_t mode);  //GPIOģʽ��ʼ������
extern int PORT_INIT(GPIO_TypeDef* GPIOx,uint8_t speed,uint8_t mode);  //һ��˿ڳ�ʼ������
extern int Fast_OutputSet(GPIO_TypeDef* GPIOx,uint8_t pin);//���������ʼ����Ĭ������Ϊ��������
extern int Fast_InputSet(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t Speed);//���������ʼ����Ĭ������Ϊ�������룬�ٶ��Զ�
extern int Change_Port_Mode(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t mode,uint8_t Speed);//�˿ڲ����ı� �ı�˿ڣ����ţ�ģʽ���ٶ�
extern int Cut_PIN_CLK(uint8_t port);//�˿ھ�Ĭ���Ͽ��˿�ʱ��
extern int Reconnect_PIN_CLK(uint8_t port);//����˿ھ�Ĭ
extern int GPIO_OUT(GPIO_TypeDef* port,uint16_t pin,BitAction data);//����ߵ͵�ƽ����
extern uint8_t GPIO_READ(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);//��ȡ����ĸߵ͵�ƽ
extern void GPIO_Write_Port(GPIO_TypeDef* GPIOx,u16 Val);//��˿���������ݣ�����Ϊ16����
extern u16 GPIO_Read_Port(GPIO_TypeDef* GPIOx);//��ȡ�˿���ʮ��λ���ݲ�����
extern void CLK_SET(uint8_t GPIOX);//ʱ�ӹ���
extern void OUT_TOGGLE(GPIO_TypeDef* GPIOx,uint16_t pin);//�����ת
#endif
