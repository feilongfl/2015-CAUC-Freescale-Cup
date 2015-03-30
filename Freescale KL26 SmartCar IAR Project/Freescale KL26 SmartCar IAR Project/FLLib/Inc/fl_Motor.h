#include "common.h"
#include "fl_pid.h"
#include "fl_cfg.h"


#ifndef _FL_MOTOR_
#define _FL_MOTOR_


//电机默认参数
#define MotorDefaultDuty 0//开机
#define MotorPIDDefaultP 1//电机默认P
#define MotorPIDDefaultI 1//电机默认I
#define MotorPIDDefaultD 1//电机默认D
//电机限制参数
#define MotorPidMinP  0//电机最小P
#define MotorPidMinI  0//电机最小I
#define MotorPidMinD  0//电机最小D
#define MotorPidMaxP  1//电机最大P
#define MotorPidMaxI  1//电机最大I
#define MotorPidMaxD  1//电机最大D

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
#define MotorSpeedMax TpmMotorPrecison
#define MotorSpeedMin 0
#endif


/************************************************************************/
/*                                                                      */
/************************************************************************/
void MotorInit();//初始化电机
//void MotorPidSet(struct Pid_s * pid);//pid设置
void MotorPidSetP(int16 p);
void MotorPidSetI(int16 i);
void MotorPidSetD(int16 d);
void MotorDutySet(int16 duty);
//////////////////////////////////////////////////////////////////////////

#endif//_FL_MOTOR_
