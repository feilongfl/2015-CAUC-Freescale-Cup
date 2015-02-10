#include "fl_ADC.h"

struct FLAdc_s FLAdcReadArr[FLAdcSaveFifoLength];//adc读取数据存储空间
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
static uint16 * AdcReadAll()
{
	uint16 * FLAdcLastAddress = &FLAdcLast.FLAdc0;
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		*FLAdcLastAddress++ = adc_once((ADCn_Ch_e)FLAdc_Ptxn[adcLoopTemp], FlAdcBit);
	}
	return &FLAdcLast.FLAdc0;
}

//归一化
uint16 AdcNormalizing()
{

}










