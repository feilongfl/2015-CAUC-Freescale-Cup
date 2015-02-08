
#include "common.h"
#include "fl_pid.h"

#warning pid��ʼֵδ�趨
//״ֵ̬
volatile struct Pid_s PidMotor = { 1, 1, 1 };//���
volatile struct Pid_s PidSteer = { 1, 1, 1 };//���
const struct Pid_s volatile *PidMotorAddress = &PidMotor;//�����ַ
const struct Pid_s volatile *PidSteerAddress = &PidSteer;//�����ַ

volatile struct Speed_s Speed = { 0, 0 };

#warning pid���ֵδ�趨
const struct Pid_s PidMotorMax = { 1, 1, 1 };//���
const struct Pid_s PidSteerMax = { 1, 1, 1 };//���
const struct Pid_s *PidMotorMaxAddress = &PidMotorMax;//�����ַ
const struct Pid_s *PidSteerMaxAddress = &PidSteerMax;//�����ַ
//��Сֵ
#warning pid��Сֵδ�趨
const struct Pid_s PidMotorMin = { 0, 0, 0 };//���
const struct Pid_s PidSteerMin = { 0, 0, 0 };//���
const struct Pid_s *PidMotorMinAddress = &PidMotorMin;//�����ַ
const struct Pid_s *PidSteerMinAddress = &PidSteerMin;//�����ַ





//////////////////////////////////////////////////////////////////////////
uint32 PidError[3] = { 0, 0 ,0};

/************************************************************************/
/*                                                                      */
/************************************************************************/
//����ֵ��ʵ��ֵ�����������֣�΢��,��֪����ʲô��������ֵ
uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold)
{
	uint32 PidOut;
	PidError[2] = Rin - Yout;//�������

	if ((PidError[2]) < PidThreshold)//������
	{
		PidOut = (uint32)/*�˴��ᵼ�����ݶ�ʧ����Ҫʵ�ʲ��ԣ�*/
			(Kp * (PidError[2] - PidError[1])
			+ Ki  * PidError[2] 
			+ Kd * (PidError[2] - 2 * PidError[1] + PidError[0]));
	}
	else
	{
		PidOut = Rin;
	}

	//�������ݣ�׼���´μ���
	PidError[0] = PidError[1];
	PidError[1] = PidError[2];
	return PidOut;
}