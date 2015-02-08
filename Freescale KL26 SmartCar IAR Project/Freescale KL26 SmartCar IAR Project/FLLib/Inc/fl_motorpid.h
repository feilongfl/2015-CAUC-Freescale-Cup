/************************************************************************/
/*       头文件                                              */
/************************************************************************/
#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
/************************************************************************/
/*              宏定义                                               */
/************************************************************************/
//电机常规属性
#define MotorDutyMax TpmMotorPrecison//最大值
//电机默认参数
#define SteerDefaultDuty 0//开机
#define MotorPIDDefaultP 1//电机默认P
#define MotorPIDDefaultI 1//电机默认I
#define MotorPIDDefaultD 1//电机默认D
//点击限制参数
#define PidMotorMin_P  0//电机最小P
#define PidMotorMin_I  0//电机最小I
#define PidMotorMin_D  0//电机最小D
#define PidMotorMax_P  1//电机最大P
#define PidMotorMax_I  1//电机最大I
#define PidMotorMax_D  1//电机最大D




