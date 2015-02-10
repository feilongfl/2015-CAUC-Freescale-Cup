#include "fl_ADC.h"

uint16 FLAdcReadArr[FLAdcMax];//adc读取原始数据
FLAdcLostLine AdcLostLine = OnLine;//丢线状态
//给个默认值防止出现问题

uint8 FLAdc_Ptxn[FLAdcMax] = {
	ADC0_DM0,
	ADC0_DM1,
	ADC0_DM2,
	ADC0_DM3,
	ADC0_DP0,
};//adc通道

//初始化
void AdcInit()
{
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		adc_init(FLAdc_Ptxn[adcLoopTemp]);
	}
}

//读取所有adc的值
static uint16 * AdcReadAll()
{
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		 FLAdcReadArr[adcLoopTemp] = adc_once(FLAdc_Ptxn[adcLoopTemp],FlAdcBit);
	}
	return FLAdcReadArr;
}

//归一化
uint16 AdcNormalizing()
{

}










