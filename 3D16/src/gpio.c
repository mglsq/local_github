#include "gpio.h"

//////////////////////////////////////////////////////
/*
GPIO��ʼ������
�������룺�˿ڣ����źţ������������������ʼ״̬���������裬�ϡ�������
*/

void GPIOInit(GPIO_TypeDef * Port,u8 Index,u8 Direction,u8 Status)
{
	u8 temp;	//
	u32* CRP;	//ָ��CRL��CRH�Ĵ���
	switch((u32)Port)
	{
		case (u32)GPIOA:
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	//��A��ʱ��
		}break;
		case (u32)GPIOB:
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	//��B��ʱ��
		}break;
		case (u32)GPIOC:
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;	//��C��ʱ��
		}break;
		case (u32)GPIOD:
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;	//��D��ʱ��
		}break;
		case (u32)GPIOE:
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;	//��E��ʱ��
		}break;
		
		default:;
	}
	
	if(Index<8)
	{
		temp = Index<<2;
		CRP = (u32*)&(Port->CRL);
	}
	else
	{
		temp = (Index-8)<<2;
		CRP = (u32*)&(Port->CRH);
	}
	
	if(Direction)	//�ж�IO�ڷ���
	{
		if( ((u32)Port == (u32)GPIOC) && (Index == 13) )
		{
			*CRP = (*CRP & (~(0x0000000f<<temp))) | (0x00000002<<temp);		//����Ϊ���������ģʽ,����ٶ�2MHz
		}
		else
		{
			*CRP = (*CRP & (~(0x0000000f<<temp))) | (0x00000003<<temp);		//����Ϊ���������ģʽ,����ٶ�50MHz
		}
		if(Status)	//�������������Ӧ��ƽ
		{
			Port->ODR |= 1<<Index;
		}
		else
		{
			Port->ODR &= ~(1<<Index);
		}
	}
	else
	{

		*CRP &= ~(0x00000003<<temp);	//����Ϊ����ģʽ
		
		if(Status==GPIO_UP)	//��������������
		{
			*CRP = (*CRP & (~(0x0000000c<<temp))) | (0x00000008<<temp);	//ʹ������������
			Port->ODR |= 1<<Index;	//��������
		}
		else if(Status==GPIO_DOWN)
		{
			*CRP = (*CRP & (~(0x0000000c<<temp))) | (0x00000008<<temp);	//ʹ������������
			Port->ODR |= 1<<Index;	//��������
		}
		else if(Status==GPIO_NOPULL)
		{
			*CRP = (*CRP & (~(0x0000000c<<temp))) | (0x00000004<<temp);	//�������룬��������
		}
		
	}
}

//���˿�
u32 GPIOReadPort(GPIO_TypeDef* Port)
{
	return Port->IDR;
}

//д�˿�
void GPIOWritePort(GPIO_TypeDef* Port,u32 GPIOData)
{
	Port->ODR = GPIOData & 0x0000ffff;
}

//��ĳ������
u8 GPIOReadBit(GPIO_TypeDef* Port,u8 Index)
{
	return (Port->IDR & (1<<Index))?1:0;
}

//дĳ������
void GPIOWriteBit(GPIO_TypeDef* Port,u8 Index,u8 GPIOData)
{
	if(GPIOData)
	{
		Port->BSRR = 1<<Index;
	}
	else
	{
		Port->BSRR = 1<<(16+Index);
	}
}

//��ĳ��������0
void GPIOResetBit(GPIO_TypeDef* Port,u8 Index)
{
	Port->BSRR = 1<<(16+Index);
}

//��ĳ��������1
void GPIOSetBit(GPIO_TypeDef* Port,u8 Index)
{
	Port->BSRR = 1<<Index;
}

//��ĳ�����ŵ�ƽ��ת
void GPIOTurnBit(GPIO_TypeDef* Port,u8 Index)
{
	Port->ODR ^= 1<<Index;
}
