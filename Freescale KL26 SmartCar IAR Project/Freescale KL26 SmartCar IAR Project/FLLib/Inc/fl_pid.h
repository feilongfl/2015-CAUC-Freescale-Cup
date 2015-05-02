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

#define PidPrecision 1000//Pid精度

#if PidPrecision < 0xff//根据精度选择数据类型
struct Pid_s
{
	int32 Integral;//积分累加值
	int32 Now;//

	uint8 P;
	uint8 I;
	uint8 D;

	int32 g;//后项差分

	uint16 Imax;//i的积分限幅
	int32 Target;
	int32 last_error;//上次误差
};
#elif PidPrecision < 0xffff
struct Pid_s
{
	int32 Integral;//积分累加值
	int32 Now;//

	uint16 P;
	uint16 I;
	uint16 D;

	int32 g;//后项差分

	int32 Imax;//i的积分限幅
	int32 Target;
	int32 last_error;//上次误差
};
#else
struct Pid_s
{
	int32 Integral;//积分累加值
	int32 Now;//

	uint32 P;
	uint32 I;
	uint32 D;

	int32 g;//后项差分

	int32 Imax;//i的积分限幅
	int32 Target;
	int32 last_error;//上次误差
};
#endif


int32 PID(struct Pid_s * maxwell);
//uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold);

#endif//_FL_PID_


