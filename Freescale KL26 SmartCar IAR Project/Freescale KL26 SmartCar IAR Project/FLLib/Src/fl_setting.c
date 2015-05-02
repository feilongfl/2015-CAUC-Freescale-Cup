#include "fl_setting.h"



static SettingErr_e DataAddWithLimit(int32 * formerNumAdd, int32 addNum, int32 limitUpper, int32 limitLower)//计算数值返回状态
{
	int64 changeTemp;
	changeTemp = *formerNumAdd + addNum;
	if (changeTemp >= limitLower && changeTemp <= limitUpper)//判断修改后是否合法
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


SettingErr_e MotorPidAdd(Pid_e pidType, int32 addNum)//修改电机pid参数
{
	switch (pidType)
	{
	case Kp:
		return DataAddWithLimit((int32 *)&(MotorPidAddress->P), addNum, MotorPidMaxP, MotorPidMinP);
		break;

	case Ki:
		return DataAddWithLimit((int32 *)&(MotorPidAddress->I), addNum, MotorPidMaxI, MotorPidMinI);
		break;

	case Kd:
		return DataAddWithLimit((int32 *)&(MotorPidAddress->D), addNum, MotorPidMaxD, MotorPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}
SettingErr_e SteerPidAdd(Pid_e pidType, int32 addNum)//修改舵机pid参数
{
	switch (pidType)
	{
#warning todo
	case Kp:
		//return DataAddWithLimit((int32 *)&(SteerPidAddress->P), addNum, SteerPidMaxP, SteerPidMinP);
		break;

	case Ki:
		//return DataAddWithLimit((int32 *)&(SteerPidAddress->I), addNum, SteerPidMaxI, SteerPidMinI);
		break;

	case Kd:
		//return DataAddWithLimit((int32 *)&(SteerPidAddress->D), addNum, SteerPidMaxD, SteerPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}

SettingErr_e MotorSpeedAdd(int32 addNum)//电机转速
{
	return DataAddWithLimit((int32 *)&(MotorSpeedAddress->Expect), addNum, MotorSpeedMax, MotorSpeedMin);
}


static SettingErr_e DataCheckAndSet(int32 * formerNumAdd, int32 expectNum, int32 limitUpper, int32 limitLower)
{
	if (expectNum >= limitLower && expectNum <= limitUpper)//判断修改后是否合法
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


SettingErr_e MotorPidSet(Pid_e pidType, int32 expectNum)//修改电机pid参数
{
	switch (pidType)
	{
	case Kp:
		return DataCheckAndSet((int32 *)&(MotorPidAddress->P), expectNum, MotorPidMaxP, MotorPidMinP);
		break;

	case Ki:
		return DataCheckAndSet((int32 *)&(MotorPidAddress->I), expectNum, MotorPidMaxI, MotorPidMinI);
		break;

	case Kd:
		return DataCheckAndSet((int32 *)&(MotorPidAddress->D), expectNum, MotorPidMaxD, MotorPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}

SettingErr_e SteerPidSet(Pid_e pidType, int32 expectNum)//修改电机pid参数
{
	switch (pidType)
	{
#warning todo
	case Kp:
		//return DataCheckAndSet((int32 *)&(SteerPidAddress->P), expectNum, SteerPidMaxP, SteerPidMinP);
		break;

	case Ki:
		//return DataCheckAndSet((int32 *)&(SteerPidAddress->I), expectNum, SteerPidMaxI, SteerPidMinI);
		break;

	case Kd:
		//return DataCheckAndSet((int32 *)&(SteerPidAddress->D), expectNum, SteerPidMaxD, SteerPidMinD);
		break;

	default:
		return SettingErrItemNotFound;
		break;
	}
}

SettingErr_e MotorSpeedSet(int32 expectNum)//电机转速
{
	return DataCheckAndSet((int32 *)&(MotorSpeedAddress->Expect), expectNum, MotorSpeedMax, MotorSpeedMin);
}