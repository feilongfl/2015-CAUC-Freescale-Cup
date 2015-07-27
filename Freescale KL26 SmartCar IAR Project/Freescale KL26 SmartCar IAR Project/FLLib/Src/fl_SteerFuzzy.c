#include "fl_SteerFuzzy.h"
#include "fl_config.h"

//////////////////////////////////////////////////////////////////////////
//���ģ�������㷨
//////////////////////////////////////////////////////////////////////////
/************************************************************************/


//ƫ��仯��
int8 LastError = 0;

//ƫ��仯�������
int8 SteerCtrlQurr[SteerOffSetSum][2 * ErrorChangeSpeedMax + 1] =
{
	6, 5, 6, 5, 6, 6, 4, 4, 3, 2, 1, 1, 0,
	6, 5, 5, 5, 5, 5, 5, 4, 3, 3, 2, 1, 0,
	6, 5, 6, 5, 6, 5, 5, 4, 4, 2, 1, 0, 0,
	5, 5, 5, 5, 5, 5, 4, 4, 3, 3, 1, 0, -1,
	5, 4, 4, 3, 3, 3, 2, 0, 0, -2, -2, -3, -3,
	4, 4, 4, 4, 3, 3, 0, 0, -2, -3, -3, -4, -4,
	4, 4, 3, 3, 3, 0, 0, 0, -1, -3, -3, -3, -5,
	3, 3, 3, 1, 0, 0, 0, -3, -3, -4, -4, -5, -5,
	3, 2, 2, 2, 0, 0, -2, -3, -3, -3, -4, -5, -5,
	2, 1, 0, 0, -1, -3, -3, -4, -4, -4, -5, -5, -5,
	0, 0, 0, -2, -3, -3, -4, -4, -5, -5, -5, -6, -6,
	0, 0, -1, -3, -3, -3, -5, -5, -5, -5, -5, -6, -6,
	0, 0, -2, -3, -3, -4, -4, -5, -5, -6, -6, -6, -6
};

//ƫ�����Ա���ֵ��
//���ͻ����������������ֳ�8
char SteerCRI[SteerGears][SteerOffSetSum] = {
	8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 4, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 4, 8, 4, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 4, 8, 4, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 4, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8,
};

//�ɲ˵�����
/*
//���pwm����
int16 SteerPwmArr[SteerGears] = {
#if 0
1000, 1200, 1400, 1500, 1600, 1800, 2000
#elif 1
1240, 1327, 1414, 1500, 1586, 1673, 1760
#elif 1
1100, 1235, 1370, 1505, 1640, 1775, 1900
#elif 1
1030, 1200, 1400, 1500, 1600, 1800, 1970
#elif 1
- 550, -300, -100, 0, 100, 300, 500
#else
1000, 1167, 1333, 1500, 1667, 1833, 2000
#endif
};
*/

/************************************************************************/
//offset:ƫ��
void SteerVagueCtrl(int16 offset)
{
	uint16 sum = 0;
	uint16 pwm = 0;
	int8 errorChanngeSpeed = 0;
	uint8 errQurr = 0;

	offset = RANGE(offset, FreecaleConfig.Config.Steer.AdcDomain, -FreecaleConfig.Config.Steer.AdcDomain) + FreecaleConfig.Config.Steer.AdcDomain + 1;//�޷�+����ԭ��

	offset /= 10 * FreecaleConfig.Config.Steer.AdcDomain / OffSetMax;//ƫ��ģ��������������
	errorChanngeSpeed = RANGE(offset - LastError, ErrorChangeSpeedMax, -ErrorChangeSpeedMax) + ErrorChangeSpeedMax;//ƫ��仯�ʣ��޷��������ڣ�����ԭ��
	LastError = offset;//����ƫ��
	//offset = SteerDirection[offset][errorChanngeSpeed];

	//printf("offset:%d\n", offset);

	if (!RANGEQurr(offset, 8, 5))//��ֱ
	{
		//����error and errorchange���������
		errQurr = SteerCtrlQurr[offset][errorChanngeSpeed] + 6;//���������ԭ��

		//���ķ���ģ��
		for (uint8 i = 0; i < SteerGears; i++)//���ĸ
		{
			if (errQurr < ErrorChangeSpeedMax)
			{
				sum += SteerCRI[i][errQurr];
				sum += SteerCRI[i][errQurr + 1];
			}
			else
			{
				sum += SteerCRI[i][errQurr];
				sum += SteerCRI[i][errQurr - 1];
			}
		}

		for (uint8 i = 0; i < SteerGears; i++)//��pwm
		{
			pwm += (SteerCenterDuty + (i - 3) * FreecaleConfig.Config.Steer.SteerDomainDif)
				* (SteerCRI[i][errQurr] + SteerCRI[i][errQurr + 1]) / sum;
		}
		SpeedForline = FreecaleConfig.Config.Motor.Speed.TurnSpeed;//���ŵ�
	}
	else//���ֱͦ�ģ��尡����������
	{
		pwm = SteerCenterDuty;
		SpeedForline = FreecaleConfig.Config.Motor.Speed.LineSpeed;//�ɰ�
	}
	//pwm = RANGE(pwm, SteerPwmArr[SteerGears - 1], SteerPwmArr[0]);//����һ��
	tpm_pwm_duty(TpmSteer, TpmSteerCh, pwm);
}
//////////////////////////////////////////////////////////////////////////

//����ɨ��
void SteerFuzzyDomainScan()
{
	uint8 exitfunc = false;

	struct FLAdc_s adcn;

	DisableInterrupts();

	LcdCls();
	LCDPrint(0, 0, "AdcDomain Max:");

	adcn = AdcNormalizing();//��ȡ��һ�����ֵ
	SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);
	FreecaleConfig.Config.Steer.AdcDomain = ABS(de);

	while (!exitfunc)
	{
		adcn = AdcNormalizing();//��ȡ��һ�����ֵ
		SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);
		FreecaleConfig.Config.Steer.AdcDomain = MAX(ABS(de), FreecaleConfig.Config.Steer.AdcDomain);

		NumShow3(FreecaleConfig.Config.Steer.AdcDomain, LcdLocal1, LcdLine2);

		switch (KeyScanWithoutIrq())//�������
		{
		case FLKeyAdcNorExit:
			exitfunc = TRUE;//�˳�
			ConfigWrite(&FreecaleConfig);
			break;

		case FLKeyReNormalizing:
			FreecaleConfig.Config.Steer.AdcDomain = ABS(de);
			break;

		default:
			break;
		}
		DELAY_MS(50);
	}

	EnableInterrupts();
}
