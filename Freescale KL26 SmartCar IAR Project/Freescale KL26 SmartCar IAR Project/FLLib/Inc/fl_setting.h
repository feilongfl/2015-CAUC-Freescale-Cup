#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_Motor.h"
#include "Fl_steer.h"
#include "fl_error.h"

//////////////////////////////////////////////////////////////////////////

//#warning pid初始值未设定
////状态值
//extern volatile struct Pid_s PidMotor;//电机
//extern volatile struct Pid_s PidSteer;//舵机
extern const struct Pid_s volatile *MotorPidAddress;//电机地址
extern const struct Pid_s volatile *SteerPidAddress;//舵机地址
//
//extern volatile struct MotorSpeed_s MotorSpeed;
extern volatile struct MotorSpeed_s * MotorSpeedAddress;
//
//#warning pid最大值未设定
//extern const struct Pid_s PidMotorMax;//电机
//extern const struct Pid_s PidSteerMax;//舵机
//extern const struct Pid_s *PidMotorMaxAddress;//电机地址
//extern const struct Pid_s *PidSteerMaxAddress;//舵机地址
////最小值
//#warning pid最小值未设定
//extern const struct Pid_s PidMotorMin;//电机
//extern const struct Pid_s PidSteerMin;//舵机
//extern const struct Pid_s *PidMotorMinAddress;//电机地址
//extern const struct Pid_s *PidSteerMinAddress;//舵机地址


/************************************************************************/
/* 操作                                                                 */
/************************************************************************/


SettingErr_e MotorPidChange(Pid_e pidType, int8 chaangeNum);//修改电机pid参数
SettingErr_e SteerPidChange(Pid_e pidType, int8 chaangeNum);//修改舵机pid参数
SettingErr_e MotorSpeedSet(int8 changeNum);//电机转速

