#include "common.h"
#include "fl_cfg.h"
#include "Fl_steer.h"

#ifndef _FL_steer_pid_
#define _FL_steer_pid_

#define SteerPIDDefaultP 10//舵机默认P
#define SteerPIDDefaultI 0//舵机默认I
#define SteerPIDDefaultD 10//舵机默认D

#define SteerPidMaxP  500//舵机最大P
#define SteerPidMaxI  0//舵机最大I
#define SteerPidMaxD  500//舵机最大D
#define SteerPidMinP  0//舵机最小P
#define SteerPidMinI  0//舵机最小I
#define SteerPidMinD  0//舵机最小D

int32 SteerCtrlUsePid(SteerDeviationDegree_e deviation);

#endif//_FL_steer_pid_
