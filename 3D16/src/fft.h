#ifndef __FFT_H__
#define __FFT_H__

#include "common.h"

struct Compx
{
	float real;
	float imag;
};

extern struct Compx dd[65]; //FFT����
extern u8 LEDHigh[16];		//FFT���16����������ָʾ�Ƹ߶�

void ProcessFFT(void);

#endif

