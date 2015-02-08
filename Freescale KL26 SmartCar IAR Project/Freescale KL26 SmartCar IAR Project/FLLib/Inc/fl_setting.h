#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_Motor.h"

//////////////////////////////////////////////////////////////////////////
typedef enum
{
	SettingAllGreen,//����

	SettingErrOverMax,//�������ֵ
	SettingErrOverMin,//������Сֵ

	SettingErrItemNotFound,//404
	
	SettingErrOther,//δ�������

	SettingErrNumbers,//��������
}SettingErr_e;//�����
//////////////////////////////////////////////////////////////////////////

#warning pid��ʼֵδ�趨
//״ֵ̬
extern volatile struct Pid_s PidMotor;//���
extern volatile struct Pid_s PidSteer;//���
extern const struct Pid_s volatile *PidMotorAddress;//�����ַ
extern const struct Pid_s volatile *PidSteerAddress;//�����ַ

extern volatile struct MotorSpeed_s MotorSpeed;

#warning pid���ֵδ�趨
extern const struct Pid_s PidMotorMax;//���
extern const struct Pid_s PidSteerMax;//���
extern const struct Pid_s *PidMotorMaxAddress;//�����ַ
extern const struct Pid_s *PidSteerMaxAddress;//�����ַ
//��Сֵ
#warning pid��Сֵδ�趨
extern const struct Pid_s PidMotorMin;//���
extern const struct Pid_s PidSteerMin;//���
extern const struct Pid_s *PidMotorMinAddress;//�����ַ
extern const struct Pid_s *PidSteerMinAddress;//�����ַ


/************************************************************************/
/* ����                                                                 */
/************************************************************************/
SettingErr_e MotorPidChange(Pid_e pidType, int8 chaangeNum);//�޸ĵ��pid����
SettingErr_e SteerPidChange(Pid_e pidType, int8 chaangeNum);//�޸Ķ��pid����
SettingErr_e MotorSpeedSet(int8 changeNum);//���ת��

