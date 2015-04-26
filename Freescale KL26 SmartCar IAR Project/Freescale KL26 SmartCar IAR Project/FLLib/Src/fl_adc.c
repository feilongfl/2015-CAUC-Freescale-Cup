#include "fl_ADC.h"

struct FLAdc_s FLAdcReadArr[FLAdcSaveBuffLength];//adc��ȡ���ݴ洢�ռ�
struct FLAdc_s FLAdcLast = {
	0,
	0,
	0,
	0,
	//0,
};//���һ��adc��ȡ��ֵ


uint8 LcdAdcNumLocation[FLAdcMax][2] = {
	{ LcdLine2, LcdLocal1 },
	{ LcdLine2, LcdLocal2 },
	{ LcdLine2, LcdLocal3 },
	{ LcdLine2, LcdLocal4 },
	//{ LcdLine3, LcdLocal1 },
};//��������


FLAdcLostLine_e AdcLostLine = OnLine;//����״̬
//����Ĭ��ֵ��ֹ��������

uint8 FLAdc_Ptxn[FLAdcMax] = {
	ADC0_DM0,
	ADC0_DP1,
	ADC0_DP2,
	ADC0_DP3,
	//ADC0_DP0,
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
	for (uint8 adcLoopTemp = 0; adcLoopTemp < FLAdcMax; adcLoopTemp++)
	{
		*FLAdcLastAddress++ = adc_once((ADCn_Ch_e)FLAdc_Ptxn[adcLoopTemp], FlAdcBit);//��ȡ������
	}
	DELAY();
	return &FLAdcLast;//���ر���ṹ���ַ
}


//��һ��
struct FLAdc_s AdcMax;//���ֵ
//struct FLAdc_s AdcMin;//��Сֵ


struct FLAdc_s AdcNormalizing()//��һ��
{
	struct FLAdc_s adcNormalizing = *AdcReadAll();
	uint16 * adcNormalizingAddress = (uint16*)&adcNormalizing;
	uint16 * adcMax = (uint16 *)&AdcMax;
	//uint16 * adcMin = (uint16 *)&AdcMin;
	
	for (uint8 loopTemp = 0; loopTemp < FLAdcMax; loopTemp++)
	{
		*(adcNormalizingAddress + (uint8)loopTemp) = (uint16)
					((*(adcNormalizingAddress + (uint8)loopTemp) - AdcMin) * AdcNormalizingPrecision //������ֵ-��Сֵ��*����
					/ (*(adcMax + (uint8)loopTemp) - AdcMin));//���ԣ����ֵ - ��Сֵ��
	}
	return adcNormalizing;
}

static void AdcNormalizingOnce()//��һ����ֵ�趨������֮ǰ�������ֵ
{
	uint16 * adcReadTemp = (uint16*)AdcReadAll();
	uint16 * adcMaxAddress = (uint16*)&AdcMax;
	//uint16 * adcMinAddress = (uint16*)&AdcMin;
	//*adcMaxAddress = *adcMinAddress = *adcReadTemp;

#ifdef DEBUG
	printf("$");
	for (uint8 ShowTemp = 0; ShowTemp < FLAdcMax; ShowTemp++)
	{
		printf("%d,", (uint16)*((uint16*)adcReadTemp + ShowTemp));
	}
	uint8 i = 8 - FLAdcMax;
	while (i--)
	{
		printf("0");
		if (i != 0)
		{
			printf(",");
		}
	}
	printf("#");
#endif


	for (uint8 loopTemp = 0; loopTemp < FLAdcMax;loopTemp++)
	{
		*(adcMaxAddress + loopTemp) = MAX(*(adcMaxAddress + loopTemp), *(adcReadTemp + loopTemp));
		//*(adcMinAddress + loopTemp) = MIN(*(adcMinAddress + loopTemp), *(adcReadTemp + loopTemp));
	}

}

static void AdcNormalizingExtremumClear()//��չ�һ����ֵ
{
	uint16 * adcReadTemp = (uint16*)AdcReadAll();
	uint16 * adcMaxAddress = (uint16*)&AdcMax;
	//uint16 * adcMinAddress = (uint16*)&AdcMin;
	//*adcMaxAddress = *adcMinAddress = *adcReadTemp;

	for (uint8 loopTemp = 0; loopTemp < FLAdcMax; loopTemp++)
	{
		*(adcMaxAddress + loopTemp) = *(adcReadTemp + loopTemp);
		//*(adcMinAddress + loopTemp) = *(adcReadTemp + loopTemp);
	}
}

void LcdAdcShow(struct FLAdc_s * flAdcn)
{
	for (uint8 lcdShowTemp = 0; lcdShowTemp < FLAdcMax; lcdShowTemp++)
	{
		NumShow((uint16)*((uint16*)flAdcn + lcdShowTemp), LcdAdcNumLocation[lcdShowTemp][LcdLocal], LcdAdcNumLocation[lcdShowTemp][LcdLine]);
	}
}

void AdcSendNowByUart()
{
	struct FLAdc_s * flAdcn = AdcReadAll();
	printf("$");
	for (uint8 ShowTemp = 0; ShowTemp < FLAdcMax; ShowTemp++)
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
		LcdAdcShow(&AdcMax);
		break;

	/*case LcdShowMin:
		LCDPrint(LcdTitleLocal, LcdTitleLine, LcdAdcTitleNorMin);
		LcdAdcShow(&AdcMin);
		break;*/

	default:
		ASSERT(TRUE);
		break;
	}
}



void AdcNormalizingInit()
{
	uint8 exitFunc = FALSE;
	LcdAdcShowMaxOrMin_e maxOrMin = LcdShowMax;//Ĭ�����ֵ
	LcdCls();
	AdcInit();//�������ʼ�������δ�����ж�RES(3)
	AdcNormalizingExtremumClear();
	while (TRUE)
	{
		if (exitFunc)//�ж��˳�
		{
			break;
		}

		AdcNormalizingOnce();//��һ��

		LCDAdcShowMaxOrMin(maxOrMin);//�������

		switch (KeyScanWithoutIrq())//�������
		{
		case FLKeyReNormalizing:
			AdcNormalizingExtremumClear();//���¹�һ��
			break;

		case FLKeyAdcNorExit:
			exitFunc = TRUE;//�˳�
			break;

		case FLKeySwitch://�л���ʾ
			//maxOrMin = (maxOrMin == LcdShowMax) ? LcdShowMin : LcdShowMax;
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




