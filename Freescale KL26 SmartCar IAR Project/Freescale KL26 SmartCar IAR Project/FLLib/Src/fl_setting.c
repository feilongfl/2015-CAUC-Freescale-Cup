#include "fl_setting.h"


static SettingErr_e DataAddWithLimit(int32 * formerNumAdd, int32 changeNum, int32 limitUpper, int32 limitLower)//������ֵ����״̬
{
	int32 changeTemp;
	changeTemp = *formerNumAdd + changeNum;
	if (changeTemp >= limitLower && changeTemp <= limitUpper)//�ж��޸ĺ��Ƿ�Ϸ�
	{
		*formerNumAdd = changeTemp;
		return SettingAllGreen;
	}
	else if (changeTemp < limitLower)
	{
		return SettingErrOverMin;
	}
	else
	{
		return SettingErrOverMax;
	}
}


SettingErr_e MotorPidChange(Pid_e pidType, int8 chaangeNum)//�޸ĵ��pid����
{
	switch (pidType)
	{
	case Kp:
		return DataAddWithLimit(&(MotorPidAddress->P), chaangeNum, MotorPidMaxP, MotorPidMinP);
		break;

	case Ki:
		return DataAddWithLimit(&(MotorPidAddress->I), chaangeNum, MotorPidMaxI, MotorPidMinI);
		break;

	case Kd:
		return DataAddWithLimit(&(MotorPidAddress->D), chaangeNum, MotorPidMaxD, MotorPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}
SettingErr_e SteerPidChange(Pid_e pidType, int32 chaangeNum)//�޸Ķ��pid����
{
	switch (pidType)
	{
	case Kp:
		return DataAddWithLimit(&(SteerPidAddress->P), chaangeNum, SteerPidMaxP, SteerPidMinP);
		break;

	case Ki:
		return DataAddWithLimit(&(SteerPidAddress->I), chaangeNum, SteerPidMaxI, SteerPidMinI);
		break;

	case Kd:
		return DataAddWithLimit(&(SteerPidAddress->D), chaangeNum, SteerPidMaxD, SteerPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}

SettingErr_e MotorSpeedSet(int32 changeNum)//���ת��
{
	return DataAddWithLimit(&(MotorSpeedAddress->Expect), changeNum, MotorSpeedMax, MotorSpeedMin);
}
