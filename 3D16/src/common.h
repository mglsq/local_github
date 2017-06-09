#ifndef	__COMMON_H__
#define	__COMMON_H__

#include "stm32f10x.h"                  // Device header
#include "math.h"
#include "string.h"

/*	�ٷ�ͷ�ļ��Ѷ���
#define	u8	unsigned	char
#define	s8	char
#define	u16	unsigned	short
#define	s16	short
#define	u32	unsigned	int
#define	s32	int
*/

#define AHBCLOCK	72000000
#define APB1CLOCK	36000000
#define	APB2CLOCK	72000000

#define DEBUG 	(1)

// user's define

typedef struct
{
	u8 TrigType;	//��������
	s16 Level;		//������ƽ
	u8 AxisType;	//��������ʾ����
	u8 XInterval;	//������,pixs
	u8 YInterval;	//������,pixs
	
	u16 ProportionV;	//��ѹ����,mV/Pix
	u16 ProPortionT;	//ʱ�����,us/Pix
	
	u32 SamplingRate;	//������,Hz
	float Gain;	//��ѹ����
}OSCControlType;

typedef struct
{
	u8 ValidFlag;	//������Ч��־λ����������ź�
	s16 Vtop;		//�����ο���ѹ��mV
	s16 Vbase;		//�ײ��ο���ѹ��mV
	s16 Amplitude;	//���,mV
	s16	VoltageMax;	//��ѹ���ֵ,mV
	s16 VoltageMid;	//��ѹƽ��ֵ,mV
	s16 VoltageMin;	//��ѹ��Сֵ,mV
	s16 Vpp;		//��ѹ���ֵ,mV
	u32 RiseTime;	//����ʱ��,us
	u32 FallTime;	//�½�ʱ��,us
	u32 Frequency;	//Ƶ��,Hz
	u32 Width;		//������,us
	u32 Period;		//����,us
	u16 Duty;		//ռ�ձ�,%
}SignalInfoType;

typedef struct
{
	u8 Page;
	u8 Row;
	u8 Setting;
}MenuType;


#endif
