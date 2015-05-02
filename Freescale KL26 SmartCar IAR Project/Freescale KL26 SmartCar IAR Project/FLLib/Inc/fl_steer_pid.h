#include "common.h"
#include "fl_cfg.h"
#include "Fl_steer.h"

#ifndef _FL_steer_pid_
#define _FL_steer_pid_

#define SteerPIDDefaultP 1//���Ĭ��P
#define SteerPIDDefaultI 1//���Ĭ��I
#define SteerPIDDefaultD 1//���Ĭ��D

#define SteerPidMaxP  1//������P
#define SteerPidMaxI  1//������I
#define SteerPidMaxD  1//������D
#define SteerPidMinP  0//�����СP
#define SteerPidMinI  0//�����СI
#define SteerPidMinD  0//�����СD

int32 SteerCtrlUsePid(SteerDeviationDegree_e deviation);

#endif//_FL_steer_pid_
