#ifndef __USART_H__
#define __USART_H__

#include "common.h"

typedef struct
{
	u8 Sending;
	u8* SendBuffer;
	u16 SendCount;
	u8 Receiving;
	u8* ReceiveBuffer;
	u16 ReceiveCount;
}USARTControl;

//Ĭ��Ϊ�첽��������ƣ�1λ��ʼλ��8λ���ݣ�1λֹͣλ
//USART1:A9,A10ΪUSART1_TX��USART1_RX
//USART2:A2,A3ΪUSART2_TX��USAR2_RX
void USARTInit(USART_TypeDef * USART,u32 Baud);

//��ͨ�Ĵ��ڷ��ͺ��������ݷ�������˳�����
void USARTSendByte(USART_TypeDef * USART,u8 value);
u8 USARTGetByte(USART_TypeDef * USART);
void USARTSendStr(USART_TypeDef * USART,u8* str,u16 lenth);

//ʹ���жϵĴ��ڷ��ͺ���������ִ���������˳�������ȴ����ݷ�����
void USARTSendByteInt(USART_TypeDef * USART,u8 value);
void USARTSendStrInt(USART_TypeDef * USART,u8* str,u16 lenth);


void EnableUSARTInt(USART_TypeDef * USART);		//����ֻ����TCIE��RXNEIE�ж�
void DisableUSARTInt(USART_TypeDef * USART);	//����ֻ�ر�TCIE��RXNEIE�ж�

void USARTSendHex(USART_TypeDef * USART,u8 value);

#endif
