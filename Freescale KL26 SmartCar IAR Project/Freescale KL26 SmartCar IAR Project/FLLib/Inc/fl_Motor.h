#include "common.h"
#include "fl_pid.h"
#include "fl_cfg.h"


#ifndef _FL_MOTOR_
#define _FL_MOTOR_

extern struct MotorSpeed_s Speed;


#if 0//结构体方式实现
#if (TpmMotorPrecison > 0xffff)
struct MotorSpeed_s
{
	uint32 Acturally;
	uint32 Expect;
	uint32 Max;
	uint32 Min;
};
#elif (TpmMotorPrecison > 0xff)
struct MotorSpeed_s
{
	uint16 Acturally;
	uint16 Expect;
	uint16 Max;
	uint16 Min;
};
#else
struct MotorSpeed_s
{
	uint8 Acturally;
	uint8 Expect;
	uint8 Max;
	uint8 Min;
};
#endif
#else//结构体和宏定义实现
#if (TpmMotorPrecison > 0xffff)
struct MotorSpeed_s
{
	uint32 Acturally;
	uint32 Expect;
};
#elif (TpmMotorPrecison > 0xff)
struct MotorSpeed_s
{
	uint16 Acturally;
	uint16 Expect;
};
#else
struct MotorSpeed_s
{
	uint8 Acturally;
	uint8 Expect;
};
#endif
#define MotorSpeedMax (TpmMotorPrecison / 3)
#define MotorSpeedMin 0
#endif


/************************************************************************/
/*                                                                      */
/************************************************************************/
void MotorInit();//初始化电机
//void MotorPidSet(struct Pid_s * pid);//pid设置

//////////////////////////////////////////////////////////////////////////

#endif//_FL_MOTOR_
