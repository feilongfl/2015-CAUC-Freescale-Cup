#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_Motor.h"

#ifndef _FL_MOTOR_PID_
#define _FL_MOTOR_PID_

//���Ĭ�ϲ���
#define MotorDefaultDuty 0//����
#define MotorPIDDefaultP 10//���Ĭ��P
#define MotorPIDDefaultI 1//���Ĭ��I
#define MotorPIDDefaultD 100//���Ĭ��D
//������Ʋ���
#define MotorPidMinP  0//�����СP
#define MotorPidMinI  0//�����СI
#define MotorPidMinD  0//�����СD
#define MotorPidMaxP  1//������P
#define MotorPidMaxI  1//������I
#define MotorPidMaxD  1//������D

void MotorPidSetP(int16 p);
void MotorPidSetI(int16 i);
void MotorPidSetD(int16 d);

int32 MotorCtrlUsePid();
void MotorCtrl();
void MotorPidInit();
#endif//_FL_MOTOR_PID_
