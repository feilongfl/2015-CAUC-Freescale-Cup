#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_Motor_pid.h"
#include "Fl_steer_pid.h"
#include "fl_error.h"


#ifndef _FL_SETTING_
#define _FL_SETTING_

//////////////////////////////////////////////////////////////////////////

//#warning pid��ʼֵδ�趨 
////״ֵ̬
//extern volatile struct Pid_s PidMotor;//���
//extern volatile struct Pid_s PidSteer;//���
extern  struct Pid_s  *MotorPidAddress;//�����ַ
extern  struct Pid_s  *SteerPidAddress;//�����ַ
//
//extern volatile struct MotorSpeed_s MotorSpeed;
extern  struct MotorSpeed_s * MotorSpeedAddress;

/************************************************************************/
/* ����                                                                 */
/************************************************************************/
SettingErr_e MotorPidAdd(Pid_e pidType, uint16 addNum);//�޸ĵ��pid����
SettingErr_e SteerPidAdd(Pid_e pidType, uint16 addNum);//�޸Ķ��pid����
SettingErr_e MotorSpeedAdd(uint16 addNum);//���ת��

SettingErr_e MotorPidSet(Pid_e pidType, uint16 expectNum);//�趨���pid����
SettingErr_e SteerPidSet(Pid_e pidType, uint16 expectNum);//�趨���pid����
SettingErr_e MotorSpeedSet(uint16 expectNum);//���ת��
#endif//_FL_SETTING_
