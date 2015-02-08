#include "Fl_steer.h"

struct Pid_s SteerPid = {
	SteerPIDDefaultP,
	SteerPIDDefaultI, 
	SteerPIDDefaultD 
};//�����ǰpid����

uint16 SteerDuty[SteerDegreeNum] = {
#warning �����ö�����ֵ����
	0  ,
	5  ,
	10 ,
	15 ,
	20 ,
	25 ,
	30 ,
	35 ,
	40 ,
	45 ,
	50 ,
	55 ,
	60 ,
	65 ,
	70 ,
	75 ,
	80 ,
	85 ,
	90 ,
	95 ,
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
};//������ֵ����

void SteerInit()
{
	tpm_pwm_init(TpmSteer, TpmSteerCh, TpmSteerFreq, SteerDefaultDuty);
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