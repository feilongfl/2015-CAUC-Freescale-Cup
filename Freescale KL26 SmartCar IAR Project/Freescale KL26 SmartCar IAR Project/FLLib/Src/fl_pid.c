

#include "fl_pid.h"

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