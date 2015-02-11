#include "fl_ADC.h"

struct FLAdc_s FLAdcReadArr[FLAdcSaveBuffLength];//adc读取数据存储空间
struct FLAdc_s FLAdcLast = {
	0,
	0,
	0,
	0,
	0,
};//最后一次adc读取数值


FLAdcLostLine_e AdcLostLine = OnLine;//丢线状态
//给个默认值防止出现问题

uint8 FLAdc_Ptxn[FLAdcMax] = {
	ADC0_DM0,
	ADC0_DM1,
	ADC0_DM2,
	ADC0_DM3,
	ADC0_DP0,
};//adc通道数组

//初始化
void AdcInit()
{
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		adc_init((ADCn_Ch_e)FLAdc_Ptxn[adcLoopTemp]);
	}
}

//读取所有adc的值
static struct FLAdc_s * AdcReadAll()
{
	uint16 * FLAdcLastAddress = (uint16 *)&FLAdcLast;
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		*FLAdcLastAddress++ = adc_once((ADCn_Ch_e)FLAdc_Ptxn[adcLoopTemp], FlAdcBit);//读取并保存
	}
	return &FLAdcLast;//返回保存结构体地址
}


//归一化
struct FLAdc_s AdcMax;//最大值
struct FLAdc_s AdcMin;//最小值


struct FLAdc_s AdcNormalizing()//归一化
{
	struct FLAdc_s adcNormalizing = *AdcReadAll();
	uint16 * adcNormalizingAddress = (uint16*)&adcNormalizing;
	uint16 * adcMax = (uint16 *)&AdcMax;
	uint16 * adcMin = (uint16 *)&AdcMin;
	
	for (uint8 loopTemp = 0; loopTemp < FLAdcMax; loopTemp++)
	{
		*(adcNormalizingAddress + (uint8)loopTemp) = (uint16)
					((*(adcNormalizingAddress + (uint8)loopTemp) - *(adcMin + (uint8)loopTemp)) * AdcNormalizingPrecision //（输入值-最小值）*精度
					/ (*(adcMax + (uint8)loopTemp) - *(adcMin + (uint8)loopTemp)));//除以（最大值 - 最小值）
	}
	return adcNormalizing;
}

static void AdcNormalizingOnce()//归一化最值设定，调用之前先清空最值
{
	uint16 * adcReadTemp = (uint16*)AdcReadAll();
	uint16 * adcMaxAddress = (uint16*)&AdcMax;
	uint16 * adcMinAddress = (uint16*)&AdcMin;
	//*adcMaxAddress = *adcMinAddress = *adcReadTemp;

	for (uint8 loopTemp = 0; loopTemp < FLAdcMax;loopTemp++)
	{
		*(adcMaxAddress + loopTemp) = max(*(adcMaxAddress + loopTemp), *(adcReadTemp + loopTemp));
		*(adcMinAddress + loopTemp) = min(*(adcMinAddress + loopTemp), *(adcReadTemp + loopTemp));
	}
}

static void AdcNormalizingExtremumClear()//清空归一化最值
{
	uint16 * adcReadTemp = (uint16*)AdcReadAll();
	uint16 * adcMaxAddress = (uint16*)&AdcMax;
	uint16 * adcMinAddress = (uint16*)&AdcMin;
	//*adcMaxAddress = *adcMinAddress = *adcReadTemp;

	for (uint8 loopTemp = 0; loopTemp < FLAdcMax; loopTemp++)
	{
		*(adcMaxAddress + loopTemp) = *(adcReadTemp + loopTemp);
		*(adcMinAddress + loopTemp) = *(adcReadTemp + loopTemp);
	}
}


unsigned char LcdAdcNumLocal[FLAdcMax][2] = {
	{ LcdLine2, LcdLocal1 },
	{ LcdLine2, LcdLocal2 },
	{ LcdLine2, LcdLocal3 },
	{ LcdLine2, LcdLocal4 },
	{ LcdLine3, LcdLocal1 },
};//数据坐标

void LcdAdcShow(struct FLAdc_s * flAdcn)
{
	for (uint8 lcdShowTemp = 0; lcdShowTemp < FLAdcMax; lcdShowTemp++)
	{
		NumShow((uint16)*((uint16*)flAdcn + lcdShowTemp), LcdAdcNumLocal[lcdShowTemp][LcdLine], LcdAdcNumLocal[lcdShowTemp][LcdLocal]);
	}
}


static void LCDAdcShowMaxOrMin(LcdAdcShowMaxOrMin_e lcdAdcType)
{
	switch (lcdAdcType)
	{
	case LcdShowMax:
		LCDPrint(LcdTitleLocal, LcdTitleLine, LcdAdcTitleNorMax);
		LcdAdcShow(&AdcMax);
		break;

	case LcdShowMin:
		LCDPrint(LcdTitleLocal, LcdTitleLine, LcdAdcTitleNorMin);
		LcdAdcShow(&AdcMin);
		break;

	default:
		ASSERT(TRUE);
		break;
	}
}



void AdcNormalizingInit()
{
	uint8 exitFunc = FALSE;
	LcdAdcShowMaxOrMin_e maxOrMin = LcdShowMax;//默认最大值
	AdcNormalizingExtremumClear();
	while (TRUE)
	{
		if (exitFunc)//判断退出
		{
			break;
		}

		AdcNormalizingOnce();//归一化

		LCDAdcShowMaxOrMin(maxOrMin);//输出数据

		switch (KeyScanWithoutIrq())//按键检测
		{
		case FLKeyReNormalizing:
			AdcNormalizingExtremumClear();//重新归一化
			break;

		case FLKeyStartCar:
			exitFunc = TRUE;//退出
			break;

		case FLKeySwitch://切换显示
			maxOrMin = (maxOrMin == LcdShowMax) ? LcdShowMin : LcdShowMax;
			break;

		default:
			break;
		}
	}
}




