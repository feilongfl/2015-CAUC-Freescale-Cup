#include "Fl_steer.h"



SteerTurnDirection_e CarDirection = SteerDirectionCenter;//��ʷ���򣬶���׼��
#define SteerDegreeNum 50//����Ƕȷ�Χ

uint16 SteerDuty[SteerDegreeNum] = {
#ifdef _FL_VISUAL_STUDIO_
#pragma region ����������
#endif
	#warning �����ö�����ֵ����
	0,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
#ifdef _FL_VISUAL_STUDIO_
#pragma endregion ����������
#endif 
};//������ֵ����

InitRepot_e SteerInit()
{
	tpm_pwm_init(TpmSteer, TpmSteerCh, TpmSteerFreq, SteerDefaultDuty);
	return InitAllGreen;
}

// void SteerTurn(SteerTurnDirection_e direction, SteerDeviationDegree_e degree)
// {
// 	ASSERT(SteerDuty[degree] <= SteerTurnMax);//�������������Ƿ�Ϸ�
// 
// 	switch (direction)
// 	{
// 	case SteerDirectionLeft:
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - SteerDuty[degree]);
// 		break;
// 
// 	case SteerDirectionCenter:
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty);
// 		break;
// 
// 	case SteerDirectionRight:
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + SteerDuty[degree]);
// 		break;
// 
// 	default:
// 		ASSERT(TRUE);
// 		break;
// 	}
// }

void StreePidSet(Pid_e steerPid, uint8 steerPidChange)
{
	ASSERT(steerPidChange <= PidPrecision);//��ֵӦС��pid����
	switch (steerPid)
	{
#warning todo
	case Kp:
		//SteerPid.P = steerPidChange;
		break;

	case Ki:
		//SteerPid.I = steerPidChange;
		break;

	case Kd:
		//SteerPid.D = steerPidChange;
		break;

	default:
		ASSERT(TRUE);
		break;
	}
}

static SteerTurnDirection_e steerDirectionSetBySum(int32 sum)
{
	sum /= 5;//���Ҳ�����˲���
#if 0
	if (sum < -SteerAngleProtectRange / 5)
	{
		return SteerDirectionRight;
	}
	else if (sum > SteerAngleProtectRange / 5)
	{
		return SteerDirectionLeft;
	}
	else
	{
		return SteerDirectionCenter;
	}
#else
	return (sum > 0) ? SteerDirectionLeft : SteerDirectionRight;
#endif
}


//////////////////////////////////////////////////////////////////////////
//����adc���㳵������
SteerTurnDirection_e SteerDirectionSetByAdcOne(struct FLAdc_s * adc_s, FLAdcLostLine_e * lostLine)
{
	uint16 * adc_addr = (uint16*)adc_s;
	int32 sum = 0;
	FLAdcLostLine_e lostLineTemp = TRUE;

	for (uint8 adcTemp = FLAdcMax; adcTemp > FLAdcMax / 2;adcTemp--)
	{
		sum += *(adc_addr + FLAdcMax - adcTemp);//����ad��-ad��
		sum -= *(adc_addr + adcTemp - 1);
		lostLineTemp &= (*(adc_addr + FLAdcMax - adcTemp) > LostLineAdcMin) ? false : true;//�ж϶���
		lostLineTemp &= (*(adc_addr + adcTemp - 1) > LostLineAdcMin) ? false : true;
	}

	*lostLine = lostLineTemp;

	switch (lostLineTemp)
	{
	case OnLine:
		return CarDirection = steerDirectionSetBySum(sum);
		break;

	case LostLine:
		return CarDirection;
		break;

	default:
		ASSERT(true);
		return CarDirection;//���Ʊ���ʱ����
		break;
	}
	
}

SteerDeviationDegree_e SteerDeviationDegreeSetByAdc(struct FLAdc_s * adc_s)
{
	uint16 * adc_addr = (uint16*)adc_s;
	int32 deviation = 0;
	int32 sum = 0;

	for (uint8 adcTemp = FLAdcMax; adcTemp > FLAdcMax / 2; adcTemp--)
	{
		deviation += *(adc_addr + FLAdcMax - adcTemp);//����ad��-ad��
		deviation -= *(adc_addr + adcTemp - 1);
	}

#ifdef SteerDegAbs
	deviation = ABS(deviation);
#endif

	for (uint8 adcTemp = 0; adcTemp < FLAdcMax; adcTemp++)
	{
		sum += *(adc_addr + adcTemp);//����ad��+ad��
	}

#if ((FLAdcMax % 2) == 1)
	sum -= *(adc_addr + (uint8)(FLAdcMax / 2) );//���������ʱ��ȥ�м�
#endif

	//�����ҵĹ�ʽ����˵�ǹٷ��Ľ������
	//��ad��-ad�ң� / ��ad�� + ad�ң� * 100
	return (SteerDeviationDegree_e)((deviation * 100 / sum));
}




//////////////////////////////////////////////////////////////////////////
//���ģ�������㷨
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*���Ա���ָ��*/
//���ƫ��仯��Χmax = 63
//����ǰƫ�����ֵmax=44
//
//ģ��������ƫ�Χ-6~6
#define SteerOffSetSum 13
//�ο�������������ǰ�ֵ�˼�룬�ݶ�7��
#define SteerGears 7
#warning �����ڲ�ͬ�������ǲ�ͬ�ģ�����ʱ��Ҫɨ�裬�������ƹ�һ������
//ƫ������
#define OffSetMax	59
//ԭ������ֵ
#define ZeroPointUp (OffSetMax + 1)
//ƫ��仯������
#define ErrorChangeSpeedMax	6

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
//���pwm����
int16 SteerPwmArr[SteerGears] = {
#if 1
	1000, 1200, 1400, 1500, 1600, 1800, 2000
#elif 0
	- 550, -300, -100, 0, 100, 300, 500
#else
	1000, 1167, 1333, 1500, 1667, 1833, 2000
#endif
};
/************************************************************************/
//offset:ƫ��
void SteerVagueCtrl(int16 offset)
{
	uint16 sum = 0;
	uint16 pwm = 0;
	int8 errorChanngeSpeed = 0;
	uint8 errQurr = 0;

	offset = RANGE(offset, OffSetMax, -OffSetMax) + ZeroPointUp;//�޷�+����ԭ��

	offset /= 10;//ƫ��ģ����
	errorChanngeSpeed = RANGE(offset - LastError, ErrorChangeSpeedMax, -ErrorChangeSpeedMax) + ErrorChangeSpeedMax;//ƫ��仯�ʣ��޷��������ڣ�����ԭ��
	LastError = offset;//����ƫ��
	//offset = SteerDirection[offset][errorChanngeSpeed];

	printf("offset:%d\n", offset);

	if (!RANGEQurr(offset, 8, 5))//��ֱ
	{
		//����error and errorchange���������
		errQurr = SteerCtrlQurr[offset][errorChanngeSpeed] + 6;//�������ԭ��
		//���ķ���ģ��
		for (uint8 i = 0; i < SteerGears; i++)//���ĸ
		{
			sum += SteerCRI[i][offset];
			sum += SteerCRI[i][offset + 1];
		}

		for (uint8 i = 0; i < SteerGears; i++)//��pwm
		{
			pwm += SteerPwmArr[i] * (SteerCRI[i][offset] + SteerCRI[i][offset + 1]) / sum;
		}
		//Speed.Expect = 500;//���ŵ�
	}
	else//���ֱͦ�ģ��尡����������
	{
		pwm = SteerCenterDuty;
		//Speed.Expect = 1000;//�ɰ�
	}
	//pwm = RANGE(pwm, SteerPwmArr[SteerGears - 1], SteerPwmArr[0]);//����һ��
	tpm_pwm_duty(TpmSteer, TpmSteerCh, pwm);
}
//////////////////////////////////////////////////////////////////////////

