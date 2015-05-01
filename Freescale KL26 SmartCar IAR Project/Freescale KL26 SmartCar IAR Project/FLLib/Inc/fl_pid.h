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

#if PidPrecision < 0xff//根据精度选择数据类型
struct Pid_s
{
	int32 Integral;//积分累加值
	int32 Now;//

	uint8 kp;
	uint8 ki;
	uint8 kd;

	int32 g;//后项差分

	int32 Imax;//i的积分限幅
	int32 Target;
	int32 last_error;//上次误差
};
#elif PidPrecision < 0xffff
struct Pid_s
{
	int32 Integral;//积分累加值
	int32 Now;//

	uint16 kp;
	uint16 ki;
	uint16 kd;

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

	uint32 kp;
	uint32 ki;
	uint32 kd;

	int32 g;//后项差分

	int32 Imax;//i的积分限幅
	int32 Target;
	int32 last_error;//上次误差
};
#endif


uint16 PID(struct Pid_s * maxwell);
//uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold);

#endif//_FL_PID_


