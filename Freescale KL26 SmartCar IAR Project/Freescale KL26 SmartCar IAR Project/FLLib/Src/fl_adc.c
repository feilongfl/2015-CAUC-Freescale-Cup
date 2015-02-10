#include "fl_ADC.h"

struct FLAdc_s FLAdcReadArr[FLAdcSaveBuffLength];//adc��ȡ���ݴ洢�ռ�
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
static struct FLAdc_s * AdcReadAll()
{
	uint16 * FLAdcLastAddress = (uint16 *)&FLAdcLast;
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax;adcLoopTemp++)
	{
		*FLAdcLastAddress++ = adc_once((ADCn_Ch_e)FLAdc_Ptxn[adcLoopTemp], FlAdcBit);//��ȡ������
	}
	return &FLAdcLast;//���ر���ṹ���ַ
}


//��һ��
struct FLAdc_s AdcMax;//���ֵ
struct FLAdc_s AdcMin;//��Сֵ

//uint16 AdcNormalizing(uint16 measure, FLAdcn_e adcn)
//{
//	uint16 * adcMax = (uint16 *)&AdcMax;
//	uint16 * adcMin = (uint16 *)&AdcMin;
//	//������ֵ-��Сֵ��/�����ֵ - ��Сֵ��
//	return (uint16)((measure - *(adcMin + (uint8)adcn)) * AdcNormalizingPrecision / (*(adcMax + (uint8)adcn) - *(adcMin + (uint8)adcn)));
//}

struct FLAdc_s AdcNormalizing()
{
	struct FLAdc_s adcNormalizing = *AdcReadAll();
	uint16 * adcNormalizingAddress = (uint16*)&adcNormalizing;
	uint16 * adcMax = (uint16 *)&AdcMax;
	uint16 * adcMin = (uint16 *)&AdcMin;
	
	for (uint8 loopTemp = 0; loopTemp < FLAdcMax; loopTemp++)
	{
		*(adcNormalizingAddress + (uint8)loopTemp) = (uint16)((*(adcNormalizingAddress + (uint8)loopTemp) - *(adcMin + (uint8)loopTemp)) * AdcNormalizingPrecision //������ֵ-��Сֵ��*����
													/ (*(adcMax + (uint8)loopTemp) - *(adcMin + (uint8)loopTemp)));//�����ֵ - ��Сֵ��
	}
}

void AdcNormalizingInit()//��һ����ֵ�趨
{
	uint16 * adcReadTemp = (uint16*)AdcReadAll();
	uint16 * adcMaxAddress = (uint16*)&AdcMax;
	uint16 * adcMinAddress = (uint16*)&AdcMin;
	*adcMaxAddress = *adcMinAddress = *adcReadTemp;

	for (uint8 loopTemp = 0; loopTemp < FLAdcMax;loopTemp++)
	{
		*(adcMaxAddress + loopTemp) = max(*(adcMaxAddress + loopTemp), *(adcReadTemp + loopTemp));
		*(adcMinAddress + loopTemp) = min(*(adcMinAddress + loopTemp), *(adcReadTemp + loopTemp));
	}
}








