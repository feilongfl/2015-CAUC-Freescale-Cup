#include "common.h"
#include "fl_cfg.h"
#include "fl_Olcd.h"
#include "MKL_adc.h"
#include "FL_Key.h"


#ifndef _FL_ADC_
#define _FL_ADC_

typedef enum 
{
	FLAdc0,
	FlAdc1,
	FLAdc2,
	FLAdc3,
	//FLAdc4,

	FLAdcMax,
}FLAdcn_e;//adcͨ��ö��

typedef enum 
{
	AdcVertical0,
	AdcVertical1,

	AdcVerticalMax
}FLAdcVertical_e;

typedef enum
{
	FLLevelAdc0,
	FlLevelAdc1,
	FLLevelAdc2,
	FLLevelAdc3,

	FLLevelAdcMax,
}FLLevelAdcn_e;//adcͨ��ö��

typedef enum
{
	FLVerticalAdc0,
	FlVerticalAdc1,
	FLVerticalAdc2,
	//LVerticalAdc3,

	FLVerticalAdcMax,
}FLVerticalAdcn_e;//adcͨ��ö��

typedef enum
{
	FLTiltAdc0,
	FlTiltAdc1,
	//LVerticalAdc3,

	FLTiltAdcMax,
}FLTiltAdcn_e;//adcͨ��ö��

typedef enum 
{
	OnLine,
	LostLine,
}FLAdcLostLine_e;//����״̬ö��

struct FLAdcVertical_s
{
	uint16 Adc0;
	uint16 Adc1;
};

struct FLAdc_s//adc�洢�ṹ
{
	uint16 FLAdc0;
	uint16 FlAdc1;
	uint16 FLAdc2;
	uint16 FLAdc3;
	//uint16 FLAdc4;
	struct FLAdcVertical_s AdcVertical;
};



#define FLAdcSaveBuffLength 50//adc��¼��������С


#define FlAdcBit ADC_8bit//adcλ��
#define calcualteAdc(num) (((num) * 3300) / 256)//ò����adc��ȡ����ֵת��ѹֵ�ļ��㹫ʽ
#define AdcNormalizingPrecision 1000//adc��һ������

//#define AdcMin	0

#define AdcFitterTimes 3

void LcdAdcShow(struct FLAdc_s * flAdcn);

#define LcdAdcTitleNorMax (unsigned char *)"��һ��--���ֵ"
#define LcdAdcTitleNorMin (unsigned char *)"��һ��--��Сֵ"



void AdcInit();//��ʼ��adcͨ��
struct FLAdc_s AdcNormalizing();//��һ��
//void AdcNormalizingOnce();//��һ����ֵ�趨
//void AdcNormalizingExtremumClear();//��չ�һ����ֵ
void AdcNormalizingInit();//��һ����ʼ��
void AdcSendNowByUart();
struct FLAdc_s AdcNormalizingWithFitter();

#endif//_FL_ADC_



