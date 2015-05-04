#include "fl_setting.h"

struct Pid_s  *MotorPidAddress = &MotorPid;
struct Pid_s  *SteerPidAddress = &SteerPid;
struct MotorSpeed_s * MotorSpeedAddress = &Speed;


static SettingErr_e DataAddWithLimit(uint16 * formerNumAdd, uint16 addNum, uint16 limitUpper, uint16 limitLower)//������ֵ����״̬
{
	int64 changeTemp;
	changeTemp = *formerNumAdd + addNum;
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


SettingErr_e MotorPidAdd(Pid_e pidType, uint16 addNum)//�޸ĵ��pid����
{
	switch (pidType)
	{
	case Kp:
		return DataAddWithLimit((uint16 *)&(MotorPidAddress->P), addNum, MotorPidMaxP, MotorPidMinP);
		break;

	case Ki:
		return DataAddWithLimit((uint16 *)&(MotorPidAddress->I), addNum, MotorPidMaxI, MotorPidMinI);
		break;

	case Kd:
		return DataAddWithLimit((uint16 *)&(MotorPidAddress->D), addNum, MotorPidMaxD, MotorPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}
SettingErr_e SteerPidAdd(Pid_e pidType, uint16 addNum)//�޸Ķ��pid����
{
	switch (pidType)
	{
	case Kp:
		return DataAddWithLimit((uint16 *)&(SteerPidAddress->P), addNum, SteerPidMaxP, SteerPidMinP);
		break;

	case Ki:
		return DataAddWithLimit((uint16 *)&(SteerPidAddress->I), addNum, SteerPidMaxI, SteerPidMinI);
		break;

	case Kd:
		return DataAddWithLimit((uint16 *)&(SteerPidAddress->D), addNum, SteerPidMaxD, SteerPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}

SettingErr_e MotorSpeedAdd(uint16 addNum)//���ת��
{
	return DataAddWithLimit((uint16 *)&(MotorSpeedAddress->Expect), addNum, MotorSpeedMax, MotorSpeedMin);
}


static SettingErr_e DataCheckAndSet(uint16 * formerNumAdd, uint16 expectNum, uint16 limitUpper, uint16 limitLower)
{
	if (expectNum >= limitLower && expectNum <= limitUpper)//�ж��޸ĺ��Ƿ�Ϸ�
	{
		*formerNumAdd = expectNum;
		return SettingAllGreen;
	}
	else if (expectNum < limitLower)
	{
		return SettingErrOverMin;
	}
	else
	{
		return SettingErrOverMax;
	}
}


SettingErr_e MotorPidSet(Pid_e pidType, uint16 expectNum)//�޸ĵ��pid����
{
	switch (pidType)
	{
	case Kp:
		return DataCheckAndSet((uint16 *)&(MotorPidAddress->P), expectNum, MotorPidMaxP, MotorPidMinP);
		break;

	case Ki:
		return DataCheckAndSet((uint16 *)&(MotorPidAddress->I), expectNum, MotorPidMaxI, MotorPidMinI);
		break;

	case Kd:
		return DataCheckAndSet((uint16 *)&(MotorPidAddress->D), expectNum, MotorPidMaxD, MotorPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}

SettingErr_e SteerPidSet(Pid_e pidType, uint16 expectNum)//�޸ĵ��pid����
{
	switch (pidType)
	{
	case Kp:
		return DataCheckAndSet((uint16 *)&(SteerPidAddress->P), expectNum, SteerPidMaxP, SteerPidMinP);
		break;

	case Ki:
		return DataCheckAndSet((uint16 *)&(SteerPidAddress->I), expectNum, SteerPidMaxI, SteerPidMinI);
		break;

	case Kd:
		return DataCheckAndSet((uint16 *)&(SteerPidAddress->D), expectNum, SteerPidMaxD, SteerPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}

SettingErr_e MotorSpeedSet(uint16 expectNum)//���ת��
{
	return DataCheckAndSet((uint16 *)&(MotorSpeedAddress->Expect), expectNum, MotorSpeedMax, MotorSpeedMin);
}