#include "fl_ADC.h"

struct FLAdc_s FLAdcReadArr[FLAdcSaveFifoLength];//adc��ȡ���ݴ洢�ռ�
struct FLAdc_s FLAdcLast = {
	0,
	0,
	0,
	0,
	0,
};//���һ��adc��ȡ��ֵ


FLAdcLostLine_e AdcLostLine = OnLine;//����״̬
//����Ĭ��ֵ��ֹ��������

uint8 FLAdc_Ptxn[FLAdcMax] = {
	ADC0_DM0,
	ADC0_DM1,
	ADC0_DM2,
	ADC0_DM3,
	ADC0_DP0,
};//adcͨ������

//��ʼ��
void AdcInit()
{
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		adc_init((ADCn_Ch_e)FLAdc_Ptxn[adcLoopTemp]);
	}
}

//��ȡ����adc��ֵ
static uint16 * AdcReadAll()
{
	uint16 * FLAdcLastAddress = &FLAdcLast.FLAdc0;
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		*FLAdcLastAddress++ = adc_once((ADCn_Ch_e)FLAdc_Ptxn[adcLoopTemp], FlAdcBit);
	}
	return &FLAdcLast.FLAdc0;
}

//��һ��
uint16 AdcNormalizing()
{

}










