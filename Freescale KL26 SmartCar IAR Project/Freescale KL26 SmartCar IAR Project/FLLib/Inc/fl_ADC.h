#include "common.h"
#include "fl_cfg.h"
#include "MKL_adc.h"


#ifndef _FL_ADC_
#define _FL_ADC_

typedef enum 
{
	FLAdc0,
	FlAdc1,
	FLAdc2,
	FLAdc3,
	FLAdc4,

	FLAdcMax,
}FLAdcn_e;//adcͨ��ö��

typedef enum 
{
	OnLine,
	LostLine,
}FLAdcLostLine_e;//����״̬ö��

struct FLAdc_s//adc�洢�ṹ
{
	uint16 FLAdc0;
	uint16 FlAdc1;
	uint16 FLAdc2;
	uint16 FLAdc3;
	uint16 FLAdc4;
};



#define FLAdcSaveBuffLength 50//adc��¼��������С


#define FlAdcBit ADC_8bit//adcλ��
#define calcualteAdc(num) ((num * 3300) / 256)//ò����adc��ȡ����ֵת��ѹֵ�ļ��㹫ʽ
#define AdcNormalizingPrecision 1000//adc��һ������


void AdcInit();//��ʼ��
uint16 AdcNormalizing(uint16 measure, FLAdcn_e adcn);//��һ��


#endif//_FL_ADC_



