#include "fl_setting.h"


SettingErr_e MotorPidChange(Pid_e pidType, int8 chaangeNum)//�޸ĵ��pid����,ע���޸�ֻ���з��ŵģ���
{
	uint8 pidChangeTemp;
	switch (pidType)
	{
	case Kp:
		pidChangeTemp = PidMotor.P + chaangeNum;
		if (pidChangeTemp >= PidMotorMin.P && pidChangeTemp <= PidMotorMax.P)//�ж��޸ĺ��Ƿ�Ϸ�
		{
			PidMotor.P = pidChangeTemp;
			return SettingAllGreen;
		}
		else if (pidChangeTemp < PidMotorMin.P)
		{
			return SettingErrOverMin;
		}
		else
		{
			return SettingErrOverMax;
		}
		break;

	case Ki:
		pidChangeTemp = PidMotor.I + chaangeNum;
		if (pidChangeTemp >= PidMotorMin.I && pidChangeTemp <= PidMotorMax.I)
		{
			PidMotor.I = pidChangeTemp;
		}
		else if (pidChangeTemp < PidMotorMin.I)
		{
			return SettingErrOverMin;
		}
		else
		{
			return SettingErrOverMax;
		}
		break;

	case Kd:
		pidChangeTemp = PidMotor.D + chaangeNum;
		if (pidChangeTemp >= PidMotorMin.D && pidChangeTemp <= PidMotorMax.D)
		{
			PidMotor.D = pidChangeTemp;
		}
		else if (pidChangeTemp < PidMotorMin.D)
		{
			return SettingErrOverMin;
		}
		else
		{
			return SettingErrOverMax;
		}
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}
SettingErr_e SteerPidChange(Pid_e pidType, int8 chaangeNum)//�޸Ķ��pid����
{
	uint8 pidChangeTemp;
	switch (pidType)
	{
	case Kp:
		pidChangeTemp = PidSteer.P + chaangeNum;
		if (pidChangeTemp >= PidSteerMin.P && pidChangeTemp <= PidSteerMax.P)
		{
			PidSteer.P = pidChangeTemp;
		}
		else if (pidChangeTemp < PidSteerMin.P)
		{
			return SettingErrOverMin;
		}
		else
		{
			return SettingErrOverMax;
		}
		break;

	case Ki:
		pidChangeTemp = PidSteer.I + chaangeNum;
		if (pidChangeTemp >= PidSteerMin.I && pidChangeTemp <= PidSteerMax.I)
		{
			PidSteer.I = pidChangeTemp;
		}
		else if (pidChangeTemp < PidSteerMin.I)
		{
			return SettingErrOverMin;
		}
		else
		{
			return SettingErrOverMax;
		}
		break;

	case Kd:
		pidChangeTemp = PidSteer.D + chaangeNum;
		if (pidChangeTemp >= PidSteerMin.D && pidChangeTemp <= PidSteerMax.D)
		{
			PidSteer.D = pidChangeTemp;
		}
		else if (pidChangeTemp < PidSteerMin.D)
		{
			return SettingErrOverMin;
		}
		else
		{
			return SettingErrOverMax;
		}
		break;

	default:
		ASSERT(TRUE);
		break;
	}
}

SettingErr_e MotorSpeedSet(int8 changeNum)//���ת��
{
	int32 SpeedChangeTemp = MotorSpeed.Expect + changeNum;
	if (SpeedChangeTemp >= MotorSpeedMin && SpeedChangeTemp <= MotorSpeedMax)
	{
		MotorSpeed.Expect = changeNum;
		return SettingAllGreen;
	}
	else if (SpeedChangeTemp > MotorSpeedMax)
	{
		return SettingErrOverMax;
	}
	else
	{
		return SettingErrOverMin;
	}
}
