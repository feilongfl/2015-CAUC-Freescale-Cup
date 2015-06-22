#include "common.h"


#ifndef _FL_PID_
#define _FL_PID_


//pid枚举
typedef enum
{
	Kp,
	Ki,
	Kd,
}Pid_e;

#define PidPrecision 100//Pid精度

struct Pid_s
{
	int32 Integral;//积分累加值
	int32 Now;//

	uint16 P;
	uint16 I;
	uint16 D;

	int32 g;//后项差分

	uint16 Imax;//i的积分限幅
	int32 Target;
	int32 last_error;//上次误差
};


int32 PID(struct Pid_s * maxwell);
//uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold);

#endif//_FL_PID_


