#include "fl_ADC.h"

uint16 FLAdcReadArr[FLAdcMax];//adc��ȡԭʼ����
FLAdcLostLine AdcLostLine = OnLine;//����״̬
//����Ĭ��ֵ��ֹ��������

uint8 FLAdc_Ptxn[FLAdcMax] = {
	ADC0_DM0,
	ADC0_DM1,
	ADC0_DM2,
	ADC0_DM3,
	ADC0_DP0,
};//adcͨ��

//��ʼ��
void AdcInit()
{
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		adc_init(FLAdc_Ptxn[adcLoopTemp]);
	}
}

//��ȡ����adc��ֵ
static uint16 * AdcReadAll()
{
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		 FLAdcReadArr[adcLoopTemp] = adc_once(FLAdc_Ptxn[adcLoopTemp],FlAdcBit);
	}
	return FLAdcReadArr;
}

//��һ��
uint16 AdcNormalizing()
{

}










