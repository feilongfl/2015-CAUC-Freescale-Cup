#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_Motor.h"

#ifndef _FL_MOTOR_PID_
#define _FL_MOTOR_PID_

int32 MotorCtrlUsePid();
void MotorCtrl();
void MotorPidInit();
#endif//_FL_MOTOR_PID_
