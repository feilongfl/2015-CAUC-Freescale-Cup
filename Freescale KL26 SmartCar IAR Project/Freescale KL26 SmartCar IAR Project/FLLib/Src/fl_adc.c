#include "fl_ADC.h"
#include "fl_config.h"

struct FLAdc_s FLAdcReadArr[FLAdcSaveBuffLength];//adc读取数据存储空间
struct FLAdc_s FLAdcLast = {
	0,
	0,
	0,
	0,
	//0,
};//最后一次adc读取数值


uint8 LcdAdcNumLocation[FLAdcMax + AdcVerticalMax][2] = {
	{ LcdLine2, LcdLocal1 },
	{ LcdLine2, LcdLocal2 },
	{ LcdLine2, LcdLocal3 },
	{ LcdLine2, LcdLocal4 },
	{ LcdLine3, LcdLocal1 },
	{ LcdLine3, LcdLocal2 }
	//{ LcdLine3, LcdLocal1 },
};//数据坐标


FLAdcLostLine_e AdcLostLine = OnLine;//丢线状态
//给个默认值防止出现问题

ADCn_Ch_e FLAdc_Ptxn[FLAdcMax] = {
	ADC0_DP1,//pte16
	ADC0_DP2,//pte18
	ADC0_DP0,//pte20
	ADC0_DP3,//pte22
	//ADC0_DM1,//pte17
	//ADC0_DM2,//pte19
	//ADC0_DM0,//pte21

	//ADC0_DP0,
};//adc通道数组
ADCn_Ch_e FLAdcVertical_Ptxn[AdcVerticalMax] = {
	ADC0_DM3, // PTE23
	//ADC0_DP3,//pte22
	ADC0_DM0,//pte21
};//adc通道数组

void AdcVerticalInit()
{
	for (uint8 adcLoopTemp = 0; adcLoopTemp < AdcVerticalMax; adcLoopTemp++)
	{
		adc_init(FLAdcVertical_Ptxn[adcLoopTemp]);
	}
}

//初始化
void AdcInit()
{
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		adc_init(FLAdc_Ptxn[adcLoopTemp]);
	}
	AdcVerticalInit();
}

//读取所有adc的值
static struct FLAdc_s * AdcReadAll()
{
	uint16 * FLAdcLastAddress = (uint16 *)&FLAdcLast;
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax; adcLoopTemp++)
	{
		*FLAdcLastAddress++ = adc_once(FLAdc_Ptxn[adcLoopTemp], FlAdcBit);//读取并保存
	}
	for (uint8 adcLoopTemp = 0; adcLoopTemp < AdcVerticalMax; adcLoopTemp++)
	{
		*FLAdcLastAddress++ = adc_once(FLAdcVertical_Ptxn[adcLoopTemp], FlAdcBit);//读取并保存
	}
	//DELAY();//吓死我了，我还以为读一次ad怎么要半秒呢
	return &FLAdcLast;//返回保存结构体地址
}


//归一化
//struct FLAdc_s AdcMax;//最大值
//struct FLAdc_s AdcMin;//最小值


struct FLAdc_s AdcNormalizing()//归一化
{
	struct FLAdc_s adcNormalizing = AdcNormalizingWithFitter();
	uint16 * adcNormalizingAddress = (uint16*)&adcNormalizing;
	uint16 * adcMax = (uint16 *)&FreecaleConfig.Config.AdcNormalMax.Adc;
	uint16 * adcMin = (uint16 *)&FreecaleConfig.Config.AdcNormalMin.Adc;
	
	for (uint8 loopTemp = 0; loopTemp < FLAdcMax + AdcVerticalMax; loopTemp++)
	{
		*(adcNormalizingAddress + (uint8)loopTemp) = (uint16)
			(
			(
				RANGE(*(adcNormalizingAddress + (uint8)loopTemp), //输入值限幅
							*(adcMax + (uint8)loopTemp),
							*(adcMin + (uint8)loopTemp)
							)
			- *(adcMin + (uint8)loopTemp)) * AdcNormalizingPrecision //（输入值-最小值）*精度
			/ (*(adcMax + (uint8)loopTemp) - *(adcMin + (uint8)loopTemp)));//除以（最大值 - 最小值）
	}
	return adcNormalizing;
}


struct FLAdc_s AdcNormalizingWithFitter()
{
	struct FLAdc_s adcNormalizing = *AdcReadAll();
	uint16 * adcNormalizingAddress = (uint16*)&adcNormalizing;

	for (uint8 LoopTimes = AdcFitterTimes - 1; LoopTimes > 0; LoopTimes--)//求和
	{
		uint16 * adcNormalizingAddresstemp = (uint16 *)AdcReadAll();
		for (uint8 loopTemp = 0; loopTemp < FLAdcMax + AdcVerticalMax; loopTemp++)
		{
			*(adcNormalizingAddress + (uint8)loopTemp) += *(adcNormalizingAddresstemp + (uint8)loopTemp);
		}
	}

	for (uint8 loopTemp = 0; loopTemp < FLAdcMax + AdcVerticalMax; loopTemp++)//平均
	{
		*(adcNormalizingAddress + (uint8)loopTemp) /= AdcFitterTimes;
	}

	return adcNormalizing;
}

static void AdcNormalizingOne()//归一化最值设定，调用之前先清空最值
{
	uint16 * adcReadTemp = (uint16*)AdcReadAll();
	uint16 * adcMaxAddress = (uint16*)&FreecaleConfig.Config.AdcNormalMax.Adc;
	uint16 * adcMinAddress = (uint16*)&FreecaleConfig.Config.AdcNormalMin.Adc;
	//*adcMaxAddress = *adcMinAddress = *adcReadTemp;
#define DEBUG_ADC
#ifdef DEBUG_ADC
	printf("$");
	for (uint8 ShowTemp = 0; ShowTemp < FLAdcMax + AdcVerticalMax; ShowTemp++)
	{
		printf("%d,", (uint16)*((uint16*)adcReadTemp + ShowTemp));
	}
	for (uint8 ShowTemp = 0; ShowTemp < FLAdcMax + AdcVerticalMax; ShowTemp++)
	{
		printf("%d", (uint16)*((uint16*)adcMaxAddress + ShowTemp));
		if (ShowTemp != FLAdcMax - 1)
		{
			printf(",");
		}
	}
// 	uint8 i = 8 - FLAdcMax;
// 	while (i--)
// 	{
// 		printf("0");
// 		if (i != 0)
// 		{
// 			printf(",");
// 		}
// 	}
	printf("#");
	DELAY_MS(100);
#endif//DEBUG_ADC


	for (uint8 loopTemp = 0; loopTemp < FLAdcMax + AdcVerticalMax; loopTemp++)
	{
#if 1
		*(adcMaxAddress + loopTemp) = MAX(*(adcMaxAddress + loopTemp), *(adcReadTemp + loopTemp));
		*(adcMinAddress + loopTemp) = MIN(*(adcMinAddress + loopTemp), *(adcReadTemp + loopTemp));
#else
#warning debuging adc
		*(adcMaxAddress + loopTemp) = 150;
#endif//0
	}
}

static void AdcNormalizingExtremumClear()//清空归一化最值
{
	uint16 * adcReadTemp = (uint16*)AdcReadAll();
	uint16 * adcMaxAddress = (uint16*)&FreecaleConfig.Config.AdcNormalMax.Adc;
	uint16 * adcMinAddress = (uint16*)&FreecaleConfig.Config.AdcNormalMin.Adc;
	*adcMaxAddress = *adcMinAddress = *adcReadTemp;

	for (uint8 loopTemp = 0; loopTemp < FLAdcMax + AdcVerticalMax; loopTemp++)
	{
		*(adcMaxAddress + loopTemp) = *(adcReadTemp + loopTemp);
		*(adcMinAddress + loopTemp) = *(adcReadTemp + loopTemp);
	}
}

void LcdAdcShow(struct FLAdc_s * flAdcn)
{
	for (uint8 lcdShowTemp = 0; lcdShowTemp < FLAdcMax + AdcVerticalMax; lcdShowTemp++)
	{
		NumShow3((uint16)*((uint16*)flAdcn + lcdShowTemp), LcdAdcNumLocation[lcdShowTemp][LcdLocal], LcdAdcNumLocation[lcdShowTemp][LcdLine]);
	}
}

void AdcSendNowByUart()
{
	struct FLAdc_s * flAdcn = AdcReadAll();
	printf("$");
	for (uint8 ShowTemp = 0; ShowTemp < FLAdcMax + AdcVerticalMax; ShowTemp++)
	{
		printf("%d,", (uint16)*((uint16*)flAdcn + ShowTemp));
	}
	uint8 i = 8 - FLAdcMax;
	while (i--)
	{
		printf("0");
		if (i!=0)
		{
			printf(",");
		}
	}
	printf("#");
}

static void LCDAdcShowMaxOrMin(LcdAdcShowMaxOrMin_e lcdAdcType)
{
	//LcdCls();
	switch (lcdAdcType)
	{
	case LcdShowMax:
		LCDPrint(LcdTitleLocal, LcdTitleLine, LcdAdcTitleNorMax);
		LcdAdcShow(&FreecaleConfig.Config.AdcNormalMax.Adc);
		break;

	case LcdShowMin:
		LCDPrint(LcdTitleLocal, LcdTitleLine, LcdAdcTitleNorMin);
		LcdAdcShow(&FreecaleConfig.Config.AdcNormalMin.Adc);
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
	LcdCls();
	AdcInit();//如果不初始化会进入未定义中断RES(3)
	AdcNormalizingExtremumClear();
	while (TRUE)
	{
		if (exitFunc)//判断退出
		{
			break;
		}

		AdcNormalizingOne();//归一化

		LCDAdcShowMaxOrMin(maxOrMin);//输出数据

		switch (KeyScanWithoutIrq())//按键检测
		{
		case FLKeyReNormalizing:
			AdcNormalizingExtremumClear();//重新归一化
			break;

		case FLKeyAdcNorExit:
//#if UseEeprom
			ConfigWrite(&FreecaleConfig);
//#endif
			exitFunc = TRUE;//退出
			break;

		case FLKeySwitch://切换显示
			maxOrMin = (maxOrMin == LcdShowMax) ? LcdShowMin : LcdShowMax;
			break;

		case FLNoKeyDown:
			break;

		default:
			ASSERT(TRUE);
			break;
		}
	}
	LcdCls();
}



void DebugAdc()
{
	AdcInit();
	struct FLAdc_s adc = AdcNormalizingWithFitter();

	while (1)
	{
		adc = AdcNormalizingWithFitter();
		printf("$%d,%d,%d,%d,%d,%d,0,0#",
			adc.FLAdc0,
			adc.FlAdc1,
			adc.FLAdc2,
			adc.FLAdc3,
			adc.AdcVertical.Adc0,
			adc.AdcVertical.Adc1
			);
		DELAY_MS(100);
	}
}

