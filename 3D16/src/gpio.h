#ifndef __GPIO_H__
#define __GPIO_H__

#include "common.h"

#define	GPIO_IN		0
#define GPIO_OUT	1
#define GPIO_LOW	0
#define GPIO_HIGH	1
#define GPIO_DOWN	0
#define GPIO_UP		1
#define GPIO_NOPULL	2

//GPIO����ٶ�Ĭ�ϸ��٣�50MHz

//PTC13��PTC14��PTC15ʹ��ǰ�����Ķ�ע������
//��������������ΪGPIOʹ�ã��ᵼ���޷�ʹ�õ��������س���
void GPIOInit(GPIO_TypeDef* Port,u8 Index,u8 Direction,u8 Status);

u32 GPIOReadPort(GPIO_TypeDef* Port);
void GPIOWritePort(GPIO_TypeDef* Port,u32 GPIOData);

u8 GPIOReadBit(GPIO_TypeDef* Port,u8 Index);
void GPIOWriteBit(GPIO_TypeDef* Port,u8 Index,u8 GPIOData);

void GPIOResetBit(GPIO_TypeDef* Port,u8 Index);
void GPIOSetBit(GPIO_TypeDef* Port,u8 Index);
void GPIOTurnBit(GPIO_TypeDef* Port,u8 Index);


#endif
