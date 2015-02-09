

#include "fl_pid.h"

//////////////////////////////////////////////////////////////////////////
uint32 PidError[3] = { 0, 0 ,0};

/************************************************************************/
/*                                                                      */
/************************************************************************/
//给定值，实际值，比例，积分，微分,不知道是什么东西，阈值
uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold)
{
	uint32 PidOut;
	PidError[2] = Rin - Yout;//计算误差

	if ((PidError[2]) < PidThreshold)//抗饱和
	{
		PidOut = (uint32)/*此处会导致数据丢失，需要实际测试！*/
			(Kp * (PidError[2] - PidError[1])
			+ Ki  * PidError[2] 
			+ Kd * (PidError[2] - 2 * PidError[1] + PidError[0]));
	}
	else
	{
		PidOut = Rin;
	}

	//保存数据，准备下次计算
	PidError[0] = PidError[1];
	PidError[1] = PidError[2];
	return PidOut;
}