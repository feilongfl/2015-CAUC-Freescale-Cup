#include "common.h"
#include "fl_pid.h"
#include "fl_cfg.h"


#ifndef _FL_MOTOR_
#define _FL_MOTOR_

extern struct MotorSpeed_s Speed;


#if 0//�ṹ�巽ʽʵ��
#if (TpmMotorPrecison > 0xffff)
struct MotorSpeed_s
{
	uint32 Acturally;
	uint32 Expect;
	uint32 Max;
	uint32 Min;
};
#elif (TpmMotorPrecison > 0xff)
struct MotorSpeed_s
{
	uint16 Acturally;
	uint16 Expect;
	uint16 Max;
	uint16 Min;
};
#else
struct MotorSpeed_s
{
	uint8 Acturally;
	uint8 Expect;
	uint8 Max;
	uint8 Min;
};
#endif
#else//�ṹ��ͺ궨��ʵ��
#if (TpmMotorPrecison > 0xffff)
struct MotorSpeed_s
{
	uint32 Acturally;
	uint32 Expect;
};
#elif (TpmMotorPrecison > 0xff)
struct MotorSpeed_s
{
	uint16 Acturally;
	uint16 Expect;
};
#else
struct MotorSpeed_s
{
	uint8 Acturally;
	uint8 Expect;
};
#endif
#define MotorSpeedMax (TpmMotorPrecison / 3)
#define MotorSpeedMin 0
#endif


/************************************************************************/
/*                                                                      */
/************************************************************************/
void MotorInit();//��ʼ�����
//void MotorPidSet(struct Pid_s * pid);//pid����

//////////////////////////////////////////////////////////////////////////

#endif//_FL_MOTOR_
