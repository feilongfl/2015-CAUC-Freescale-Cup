#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_Motor.h"

#ifndef _FL_MOTOR_PID_
#define _FL_MOTOR_PID_

//电机默认参数
#define MotorDefaultDuty 0//开机
#define MotorPIDDefaultP 15//电机默认P
#define MotorPIDDefaultI 1//电机默认I
#define MotorPIDDefaultD 1//电机默认D
//电机限制参数
#define MotorPidMinP  0//电机最小P
#define MotorPidMinI  0//电机最小I
#define MotorPidMinD  0//电机最小D
#define MotorPidMaxP  100//电机最大P
#define MotorPidMaxI  100//电机最大I
#define MotorPidMaxD  100//电机最大D

extern struct Pid_s MotorPid;

void MotorPidSetP(int16 p);
void MotorPidSetI(int16 i);
void MotorPidSetD(int16 d);

int32 MotorCtrlUsePid();
void MotorCtrl();
void MotorPidInit();
#endif//_FL_MOTOR_PID_
