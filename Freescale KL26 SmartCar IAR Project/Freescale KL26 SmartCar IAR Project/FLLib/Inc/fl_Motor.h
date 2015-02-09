#include "common.h"
#include "fl_pid.h"
#include "fl_cfg.h"


//电机常规属性
#define MotorDutyMax TpmMotorPrecison//最大值
//电机默认参数
#define SteerDefaultDuty 0//开机
#define MotorPIDDefaultP 1//电机默认P
#define MotorPIDDefaultI 1//电机默认I
#define MotorPIDDefaultD 1//电机默认D
//点击限制参数
#define MotorPidMinP  0//电机最小P
#define MotorPidMinI  0//电机最小I
#define MotorPidMinD  0//电机最小D
#define MotorPidMaxP  1//电机最大P
#define MotorPidMaxI  1//电机最大I
#define MotorPidMaxD  1//电机最大D



#if 0//结构体方式实现
#if (TpmMotorPrecison > 255)
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
#if (TpmMotorPrecison > 255)
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
//////////////////////////////////////////////////////////////////////////
