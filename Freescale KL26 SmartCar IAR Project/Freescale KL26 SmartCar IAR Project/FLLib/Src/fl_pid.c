

#include "fl_pid.h"

//////////////////////////////////////////////////////////////////////////
uint32 PidError[3] = { 0, 0 ,0};

/************************************************************************/
/*                                                                      */
/************************************************************************/
//����ֵ��ʵ��ֵ�����������֣�΢��,��֪����ʲô��������ֵ
//uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold)
//{
//	uint32 PidOut;
//	PidError[2] = Rin - Yout;//�������
//
//	if ((PidError[2]) < PidThreshold)//������
//	{
//		PidOut = (uint32)/*�˴��ᵼ�����ݶ�ʧ����Ҫʵ�ʲ��ԣ�*/
//			(Kp * (PidError[2] - PidError[1])
//			+ Ki  * PidError[2] 
//			+ Kd * (PidError[2] - 2 * PidError[1] + PidError[0]));
//	}
//	else
//	{
//		PidOut = Rin;
//	}
//
//	//�������ݣ�׼���´μ���
//	PidError[0] = PidError[1];
//	PidError[1] = PidError[2];
//	return PidOut;
//}





int32 PID(struct Pid_s * maxwell) 
{
	float Nyquist = 0;
	float error = 0;

	error = maxwell->Target - maxwell->Now;
	maxwell->g = maxwell->last_error - error;

	Nyquist = error * maxwell->kp / PidPrecision 
		+ maxwell->Integral * maxwell->ki / PidPrecision 
		- maxwell->g * maxwell->kd / PidPrecision;


	maxwell->Integral += error / 20;      //��������ƻ���ʱ��

	if (maxwell->Integral > maxwell->Imax)
	{
		maxwell->Integral = maxwell->Imax;
	}
	if (maxwell->Integral < -maxwell->Imax)
	{
		maxwell->Integral = -maxwell->Imax;
	}

	maxwell->last_error = error;

	return (int32)(Nyquist * PidPrecision);
}

