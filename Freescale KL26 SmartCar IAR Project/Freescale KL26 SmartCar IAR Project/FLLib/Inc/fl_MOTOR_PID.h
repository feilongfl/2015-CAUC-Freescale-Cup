#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_Motor.h"

#ifndef _FL_MOTOR_PID_
#define _FL_MOTOR_PID_

//���Ĭ�ϲ���
#define MotorDefaultDuty 0//����
#define MotorPIDDefaultP 15//���Ĭ��P
#define MotorPIDDefaultI 1//���Ĭ��I
#define MotorPIDDefaultD 1//���Ĭ��D
//������Ʋ���
#define MotorPidMinP  0//�����СP
#define MotorPidMinI  0//�����СI
#define MotorPidMinD  0//�����СD
#define MotorPidMaxP  100//������P
#define MotorPidMaxI  100//������I
#define MotorPidMaxD  100//������D

extern struct Pid_s MotorPid;

void MotorPidSetP(int16 p);
void MotorPidSetI(int16 i);
void MotorPidSetD(int16 d);

int32 MotorCtrlUsePid();
void MotorCtrl();
void MotorPidInit();
#endif//_FL_MOTOR_PID_
