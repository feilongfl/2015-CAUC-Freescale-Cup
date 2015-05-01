#include "fl_steer_pid.h"

struct Pid_s SteerPid = {
	SteerPIDDefaultP,
	SteerPIDDefaultI,
	SteerPIDDefaultD
};//舵机当前pid参数

#define SteerDeviation_ArrayLength 3
uint16 SteerDeviation[SteerDeviation_ArrayLength] = { 0, 0, 0 };

static void SteerDeviation_Add(uint16 num)
{
	for (uint8 i = 0; i < SteerDeviation_ArrayLength - 1;i++)
	{
		SteerDeviation[i] = SteerDeviation[i + 1];
	}
	SteerDeviation[SteerDeviation_ArrayLength - 1] = num;
}

int32 SteerCtrlUsePid(SteerTurnDirection_e direction, SteerDeviationDegree_e deviation)
{
	SteerDeviation_Add(deviation);
	int8 dir = (uint8)direction - 1;
	return dir *
		SteerPid.P / PidPrecision * SteerDeviation[2] +
		SteerPid.I / PidPrecision * (SteerDeviation[2] - SteerDeviation[0]) +
		SteerPid.D / PidPrecision * (SteerDeviation[2] - SteerDeviation[1]);
}
