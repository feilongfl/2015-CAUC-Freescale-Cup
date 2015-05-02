#include "common.h"
#include "fl_cfg.h"
#include "Fl_steer.h"

#ifndef _FL_steer_pid_
#define _FL_steer_pid_

#define SteerPIDDefaultP 10//���Ĭ��P
#define SteerPIDDefaultI 0//���Ĭ��I
#define SteerPIDDefaultD 10//���Ĭ��D

#define SteerPidMaxP  500//������P
#define SteerPidMaxI  0//������I
#define SteerPidMaxD  500//������D
#define SteerPidMinP  0//�����СP
#define SteerPidMinI  0//�����СI
#define SteerPidMinD  0//�����СD

int32 SteerCtrlUsePid(SteerDeviationDegree_e deviation);

#endif//_FL_steer_pid_
