#include "usart.h"
#include "stdio.h"
USARTControl USART1Control;
USARTControl USART2Control;
USARTControl USART3Control;

const u8 HexTable[]="0123456789ABCDEF";

//Ĭ��Ϊ�첽��������ƣ�1λ��ʼλ��8λ���ݣ�1λֹͣλ
void USARTInit(USART_TypeDef * USART,u32 Baud)
{
	Baud *= 16;
	switch((u32)USART)
	{
		case (u32)USART1:
		{
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;	//ʹ��USART1ʱ��
			USART->BRR = ((APB2CLOCK/Baud)<<4) | ((APB2CLOCK%Baud)*16/Baud);	//���ò�����
			//��������Ϊ���ù���
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	//��A��ʱ��
			GPIOA->CRH = (GPIOA->CRH & 0xfffff00f) | (0x000008b0);	//����A9,A10ΪUSART1_TX��USART1_RX
			GPIOA->ODR |= 1<<10;
			
			USART1Control.Sending = 0;
			USART1Control.SendCount = 0;
			USART1Control.Receiving = 0;
			USART1Control.ReceiveCount = 0;
			
		}break;
		case (u32)USART2:
		{
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	//ʹ��USART2ʱ��
			USART->BRR = ((APB1CLOCK/Baud)<<4) | ((APB1CLOCK%Baud)*16/Baud);	//���ò�����
			//��������Ϊ���ù���
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	//��A��ʱ��
			GPIOA->CRL = (GPIOA->CRL & 0xffff00ff) | (0x00008b00);	//����A2,A3ΪUSART2_TX��USAR2_RX
			GPIOA->ODR |= 1<<3;
			
			USART2Control.Sending = 0;
			USART2Control.SendCount = 0;
			USART2Control.Receiving = 0;
			USART2Control.ReceiveCount = 0;
			
		}break;
		case (u32)USART3:
		{
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN;	//ʹ��USART3ʱ��
			USART->BRR = ((APB1CLOCK/Baud)<<4) | ((APB1CLOCK%Baud)*16/Baud);	//���ò�����
			//��������Ϊ���ù���
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	//��B��ʱ��
			GPIOB->CRH = (GPIOB->CRH & 0xffff00ff) | (0x00008b00);	//����B10,B11ΪUSART3_TX��USAR3_RX
			GPIOB->ODR |= 1<<11;
			
			USART3Control.Sending = 0;
			USART3Control.SendCount = 0;
			USART3Control.Receiving = 0;
			USART3Control.ReceiveCount = 0;
			
		}break;
		default:;
	}
	
	USART->CR1 |= USART_CR1_UE;	//ʹ��USART
	USART->CR1 |= USART_CR1_TE;	//ʹ�ܷ���
	USART->CR1 |= USART_CR1_RE;	//ʹ�ܽ���
	
//	USART->CR2;	//Ĭ��
//	USART->CR3;	//Ĭ��
//	USART->GTPR;//Ĭ��
	
}

void USARTSendByte(USART_TypeDef * USART,u8 value)
{
	while((USART->SR & USART_SR_TXE) == 0);	//�ȴ����ݼĴ���Ϊ��
	USART->DR = value;
	while((USART->SR & USART_SR_TC) == 0);	//�ȴ��������
	USART->SR &= ~(USART_SR_TC);	//���������ɱ�־
}

u8 USARTGetByte(USART_TypeDef * USART)
{
	while((USART->SR & USART_SR_RXNE) == 0);	//�ȴ���������
	return USART->DR;
}

void USARTSendStr(USART_TypeDef * USART,u8* str,u16 lenth)
{
	if(lenth)
	{
		while(lenth--)
		{
			USARTSendByte(USART,*str++);
		}
	}
	else
	{
		while(*str)
		{
			USARTSendByte(USART,*str++);
		}
	}
}


void USARTSendByteInt(USART_TypeDef * USART,u8 value)
{
	switch((u32)USART)
	{
		case (u32)USART1:
		{
			while(USART1Control.Sending);	//�ȴ�����ռ�ñ��ͷ�
			USART1Control.Sending = 1;		//����ռ�ñ�־λ
			USART1Control.SendCount = 1;	//����Ҫ���͵��ֽ���
		}break;
		case (u32)USART2:
		{
			while(USART2Control.Sending);
			USART2Control.Sending = 1;
			USART2Control.SendCount = 1;
		}break;
		default:;
		case (u32)USART3:
		{
			while(USART3Control.Sending);
			USART3Control.Sending = 1;
			USART3Control.SendCount = 1;
		}break;
	}
	USART->DR = value;	//����Ҫ���͵�����
}

void USARTSendStrInt(USART_TypeDef * USART,u8* str,u16 lenth)
{
	switch((u32)USART)
	{
		case (u32)USART1:
		{
			while(USART1Control.Sending);	//�ȴ�����ռ�ñ��ͷ�
			USART1Control.Sending = 1;		//����ռ�ñ�־λ
			if(lenth)	//���ָ�������ݳ��ȣ���ָ�����ȷ��͡����ûָ�����ݳ��ȣ��Զ������ַ�������
			{
				USART1Control.SendCount = lenth;	
			}
			else
			{
				USART1Control.SendCount = strlen((char*)str);
			}
			USART1Control.SendBuffer = str;				//���÷��ͻ�����ָ��
			USART1->DR = *USART1Control.SendBuffer++;	//�����һ�����ݣ�������ƶ�ָ��
		}break;
		case (u32)USART2:
		{
			while(USART2Control.Sending);
			USART2Control.Sending = 1;
			if(lenth)
			{
				USART2Control.SendCount = lenth;	
			}
			else
			{
				USART2Control.SendCount = strlen((char*)str);
			}
			USART2Control.SendBuffer = str;
			USART2->DR = *USART2Control.SendBuffer++;
		}break;
		case (u32)USART3:
		{
			while(USART3Control.Sending);
			USART3Control.Sending = 1;
			if(lenth)
			{
				USART3Control.SendCount = lenth;	
			}
			else
			{
				USART3Control.SendCount = strlen((char*)str);
			}
			USART3Control.SendBuffer = str;
			USART3->DR = *USART3Control.SendBuffer++;
		}break;
		default:;
	}
}


//����ֻ����TCIE��RXNEIE�ж�
void EnableUSARTInt(USART_TypeDef * USART)
{
	switch((u32)USART)
	{
		case (u32)USART1:
		{
			NVIC_EnableIRQ(USART1_IRQn);	//�����ں˽���USART1�ж�
		}break;
		case (u32)USART2:
		{
			NVIC_EnableIRQ(USART2_IRQn);	//�����ں˽���USART2�ж�
		}break;
		case (u32)USART3:
		{
			NVIC_EnableIRQ(USART3_IRQn);	//�����ں˽���USART2�ж�
		}break;
		default:;
	}
	USART->CR1 |= USART_CR1_TCIE;	//ʹ�ܷ�������ж�
	USART->CR1 |= USART_CR1_RXNEIE;	//ʹ�ܽ�������ж�
}

//����ֻ�ر�TCIE��RXNEIE�ж�
void DisableUSARTInt(USART_TypeDef * USART)
{
	switch((u32)USART)
	{
		case (u32)USART1:
		{
			NVIC_DisableIRQ(USART1_IRQn);	//��ֹ�ں˽���USART1�ж�
		}break;
		case (u32)USART2:
		{
			NVIC_DisableIRQ(USART2_IRQn);	//��ֹ�ں˽���USART2�ж�
		}break;
		case (u32)USART3:
		{
			NVIC_DisableIRQ(USART2_IRQn);	//��ֹ�ں˽���USART2�ж�
		}break;
		default:;
	}
	USART->CR1 &= ~USART_CR1_TCIE;		//��ֹ��������ж�
	USART->CR1 &= ~USART_CR1_RXNEIE;	//��ֹ��������ж�
}


void USARTSendHex(USART_TypeDef * USART,u8 value)
{
	static u8 HexBuf[5] = {'0','X','0','0',' '};
	if((u32)USART == (u32)USART1)
	{
		while(USART1Control.Sending);	//�ȴ�����1ռ�ñ��ͷ�
		HexBuf[2] = HexTable[value/16];
		HexBuf[3] = HexTable[value%16];
		USARTSendStrInt(USART1,HexBuf,5);
	}
	else if((u32)USART == (u32)USART2)
	{
		while(USART2Control.Sending);	//�ȴ�����2ռ�ñ��ͷ�
		HexBuf[2] = HexTable[value/16];
		HexBuf[3] = HexTable[value%16];
		USARTSendStrInt(USART2,HexBuf,5);
	}
	else if((u32)USART == (u32)USART3)
	{
		while(USART3Control.Sending);	//�ȴ�����2ռ�ñ��ͷ�
		HexBuf[2] = HexTable[value/16];
		HexBuf[3] = HexTable[value%16];
		USARTSendStrInt(USART3,HexBuf,5);
	}
	
}


void USART1_IRQHandler(void)
{
	if(USART1->SR & USART_SR_TC)	//�ж������Ƿ������
	{
		USART1->SR &= ~USART_SR_TC;		//���������ɱ�־λ
		if(USART1Control.SendCount>1)	//������ͼ���������1��˵���������ݴ�����
		{
			USART1Control.SendCount--;
			USART1->DR = *USART1Control.SendBuffer++;	//��������͵����ݣ�ָ�����
		}
		else
		{
			USART1Control.SendCount = 0;	//
			USART1Control.Sending = 0;		//�������ռ�ñ�־
		}
	}
	if(USART1->SR & USART_SR_RXNE)	//�ж��Ƿ���յ�����
	{
		USART1->SR &= ~USART_SR_RXNE;	//��������ݼĴ����ǿձ�־λ
		//���ý��յĴ�����룬���磺
//		USART1Control.Receiving = 1;
//		USART1Control.ReceiveCount++;
//		USART1Control.ReceiveBuffer[USART1Control.ReceiveCount] = USART1->DR;
	}
}

void USART2_IRQHandler(void)
{
	if(USART2->SR & USART_SR_TC)	//�ж������Ƿ������
	{
		USART2->SR &= ~USART_SR_TC;		//���������ɱ�־λ
		if(USART2Control.SendCount>1)	//������ͼ���������1��˵���������ݴ�����
		{
			USART2Control.SendCount--;
			USART2->DR = *USART2Control.SendBuffer++;	//��������͵����ݣ�ָ�����
		}
		else
		{
			USART2Control.SendCount = 0;
			USART2Control.Sending = 0;		//�������ռ�ñ�־
		}
	}
	if(USART2->SR & USART_SR_RXNE)	//�ж��Ƿ���յ�����
	{
		USART2->SR &= ~USART_SR_RXNE;	//��������ݼĴ����ǿձ�־λ
		//���ý��յĴ�����룬���磺
//		USART2Control.Receiving = 1;
//		USART2Control.ReceiveCount++;
//		USART2Control.ReceiveBuffer[USART1Control.ReceiveCount] = USART1->DR;
	}
}

void USART3_IRQHandler(void)
{
	if(USART3->SR & USART_SR_TC)	//�ж������Ƿ������
	{
		USART3->SR &= ~USART_SR_TC;		//���������ɱ�־λ
		if(USART3Control.SendCount>1)	//������ͼ���������1��˵���������ݴ�����
		{
			USART3Control.SendCount--;
			USART3->DR = *USART3Control.SendBuffer++;	//��������͵����ݣ�ָ�����
		}
		else
		{
			USART3Control.SendCount = 0;
			USART3Control.Sending = 0;		//�������ռ�ñ�־
		}
	}
	if(USART3->SR & USART_SR_RXNE)	//�ж��Ƿ���յ�����
	{
		USART3->SR &= ~USART_SR_RXNE;	//��������ݼĴ����ǿձ�־λ
		//���ý��յĴ�����룬���磺
//		USART3Control.Receiving = 1;
//		USART3Control.ReceiveCount++;
//		USART3Control.ReceiveBuffer[USART3Control.ReceiveCount] = USART1->DR;
	}
}

int fputc(int ch, FILE *f)
{
	USARTSendByte(USART1, (unsigned char) ch);
	return (ch);
}














