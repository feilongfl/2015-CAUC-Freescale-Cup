/************************************************************************/
/*       ͷ�ļ�                                              */
/************************************************************************/
#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
/************************************************************************/
/*              �궨��                                               */
/************************************************************************/
//�����������
#define MotorDutyMax TpmMotorPrecison//���ֵ
//���Ĭ�ϲ���
#define SteerDefaultDuty 0//����
#define MotorPIDDefaultP 1//���Ĭ��P
#define MotorPIDDefaultI 1//���Ĭ��I
#define MotorPIDDefaultD 1//���Ĭ��D
//������Ʋ���
#define PidMotorMin_P  0//�����СP
#define PidMotorMin_I  0//�����СI
#define PidMotorMin_D  0//�����СD
#define PidMotorMax_P  1//������P
#define PidMotorMax_I  1//������I
#define PidMotorMax_D  1//������D




