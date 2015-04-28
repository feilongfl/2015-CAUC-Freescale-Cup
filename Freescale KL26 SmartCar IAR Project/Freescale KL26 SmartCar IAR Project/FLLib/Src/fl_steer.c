#include "Fl_steer.h"

struct Pid_s SteerPid = {
	SteerPIDDefaultP,
	SteerPIDDefaultI, 
	SteerPIDDefaultD 
};//�����ǰpid����

SteerTurnDirection_e CarDirection = SteerDirectionCenter;//��ʷ���򣬶���׼��

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

void SteerTurn(SteerTurnDirection_e direction, SteerTurnDegree_e degree)
{
	ASSERT(SteerDuty[degree] <= SteerTurnMax);//�������������Ƿ�Ϸ�

	switch (direction)
	{
	case SteerDirectionLeft:
		tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - SteerDuty[degree]);
		break;

	case SteerDirectionCenter:
		tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty);
		break;

	case SteerDirectionRight:
		tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + SteerDuty[degree]);
		break;

	default:
		ASSERT(TRUE);
		break;
	}
}

void StreePidSet(Pid_e steerPid, uint8 steerPidChange)
{
	ASSERT(steerPidChange <= PidPrecision);//��ֵӦС��pid����
	switch (steerPid)
	{
	case Kp:
		SteerPid.P = steerPidChange;
		break;

	case Ki:
		SteerPid.I = steerPidChange;
		break;

	case Kd:
		SteerPid.D = steerPidChange;
		break;

	default:
		ASSERT(TRUE);
		break;
	}
}

static SteerTurnDirection_e steerDirectionSetBySum(int32 sum)
{
	sum /= 5;//���Ҳ�����˲���
	if (sum < -SteerAngleProtectRange / 5)
	{
		return SteerDirectionLeft;
	}
	else if (sum > SteerAngleProtectRange / 5)
	{
		return SteerDirectionRight;
	}
	else
	{
		return SteerDirectionCenter;
	}
}


//////////////////////////////////////////////////////////////////////////
//����adc���㳵������
SteerTurnDirection_e SteerDirectionSetByAdcOne(struct FLAdc_s * adc_s)
{
	uint16 * adc_addr = (uint16*)adc_s;
	int32 sum = 0;
	uint8 lostLine = false;

	for (uint8 adcTemp = ADC_MAX; adcTemp > ADC_MAX / 2;adcTemp--)
	{
		sum += *(adc_addr + ADC_MAX - adcTemp);//����ad��-ad��
		sum -= *(adc_addr + adcTemp - 1);
		lostLine = (*(adc_addr + ADC_MAX - adcTemp) > LostLineAdcMin) ? false : true;//�ж϶���
		lostLine = (*(adc_addr + adcTemp - 1) > LostLineAdcMin) ? false : true;
	}

	switch (lostLine)
	{
	case false:
		return steerDirectionSetBySum(sum);
		break;

	case true:
		return CarDirection;
		break;

	default:
		ASSERT(true);
		return CarDirection;//���Ʊ���ʱ����
		break;
	}
	
}

SteerTurnDegree_e SteerTurnDegreeSetByAdc(struct FLAdc_s * adc_s)
{
	uint16 * adc_addr = (uint16*)adc_s;
	int32 deviation = 0;
	int32 sum = 0;

	for (uint8 adcTemp = ADC_MAX; adcTemp > ADC_MAX / 2; adcTemp--)
	{
		deviation += *(adc_addr + ADC_MAX - adcTemp);//����ad��-ad��
		deviation -= *(adc_addr + adcTemp - 1);
	}

	deviation = ABS(deviation);

	for (uint8 adcTemp = 0; adcTemp < ADC_MAX; adcTemp++)
	{
		sum += *(adc_addr + adcTemp);//����ad��+ad��
	}

#if ((ADC_MAX % 2) == 1)
	sum -= *(adc_addr + (uint8)(ADC_MAX / 2) );//���������ʱ��ȥ�м�
#endif

	//�����ҵĹ�ʽ����˵�ǹٷ��Ľ������
	//��ad��-ad�ң� / ��ad�� + ad�ң� * 100
	return (SteerTurnDegree_e)((deviation / sum) * 100);
}
