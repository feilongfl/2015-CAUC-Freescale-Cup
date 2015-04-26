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
}FLAdcn_e;//adc通道枚举

typedef enum 
{
	OnLine,
	LostLine,
}FLAdcLostLine_e;//丢线状态枚举

struct FLAdc_s//adc存储结构
{
	uint16 FLAdc0;
	uint16 FlAdc1;
	uint16 FLAdc2;
	uint16 FLAdc3;
	//uint16 FLAdc4;
};



#define FLAdcSaveBuffLength 50//adc记录缓冲区大小


#define FlAdcBit ADC_8bit//adc位数
#define calcualteAdc(num) (((num) * 3300) / 256)//貌似是adc读取的数值转电压值的计算公式
#define AdcNormalizingPrecision 1000//adc归一化精度

#define AdcMin	0

#define AdcFitterTimes 3

void LcdAdcShow(struct FLAdc_s * flAdcn);

#define LcdAdcTitleNorMax (unsigned char *)"归一化--最大值"
//#define LcdAdcTitleNorMin (unsigned char *)"归一化--最小值"



void AdcInit();//初始化adc通道
struct FLAdc_s AdcNormalizing();//归一化
//void AdcNormalizingOnce();//归一化最值设定
//void AdcNormalizingExtremumClear();//清空归一化最值
void AdcNormalizingInit();//归一化初始化
void AdcSendNowByUart();
struct FLAdc_s AdcNormalizingWithFitter();
#endif//_FL_ADC_



