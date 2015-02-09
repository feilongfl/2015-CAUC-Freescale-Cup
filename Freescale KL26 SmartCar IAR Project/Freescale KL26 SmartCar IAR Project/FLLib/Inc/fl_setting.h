#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_Motor.h"
#include "Fl_steer.h"
#include "fl_error.h"


#ifndef _FL_SETTING_
#define _FL_SETTING_

//////////////////////////////////////////////////////////////////////////

//#warning pid初始值未设定
////状态值
//extern volatile struct Pid_s PidMotor;//电机
//extern volatile struct Pid_s PidSteer;//舵机
extern  struct Pid_s  *MotorPidAddress;//电机地址
extern  struct Pid_s  *SteerPidAddress;//舵机地址
//
//extern volatile struct MotorSpeed_s MotorSpeed;
extern  struct MotorSpeed_s * MotorSpeedAddress;

/************************************************************************/
/* 操作                                                                 */
/************************************************************************/
SettingErr_e MotorPidAdd(Pid_e pidType, int32 addNum);//修改电机pid参数
SettingErr_e SteerPidAdd(Pid_e pidType, int32 addNum);//修改舵机pid参数
SettingErr_e MotorSpeedAdd(int32 addNum);//电机转速

SettingErr_e MotorPidSet(Pid_e pidType, int32 expectNum);//设定电机pid参数
SettingErr_e SteerPidSet(Pid_e pidType, int32 expectNum);//设定舵机pid参数
SettingErr_e MotorSpeedSet(int32 expectNum);//电机转速
#endif//_FL_SETTING_
