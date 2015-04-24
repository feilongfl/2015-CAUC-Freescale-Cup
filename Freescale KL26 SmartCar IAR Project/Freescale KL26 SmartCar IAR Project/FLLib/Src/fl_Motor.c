#include "fl_motor.h"

struct Pid_s * MotorPid;
struct MotorSpeed_s *Speed ;

//void MotorPidSet(struct Pid_s * pid)
//{
//	ASSERT(pid->P > MotorPidMinP && pid->P < MotorPidMaxP);
//	ASSERT(pid->I > MotorPidMinI && pid->I < MotorPidMaxI);
//	ASSERT(pid->D > MotorPidMinD && pid->D < MotorPidMaxD);
//	MotorPid = pid;
//}

void MotorPidSetP(int16 p)
{
	ASSERT(p > MotorPidMinP && p < MotorPidMaxP);
	MotorPid->P = p;
}

void MotorPidSetI(int16 i)
{
	ASSERT(i > MotorPidMinI && i < MotorPidMaxI);
	MotorPid->I = i;
}

void MotorPidSetD(int16 d)
{
	ASSERT(d > MotorPidMinD && d < MotorPidMaxD);
	MotorPid->D = d;
}

void MotorInit()
{
	ASSERT(MotorPid->P > MotorPidMinP && MotorPid->P < MotorPidMaxP);
	MotorPid->P = MotorPIDDefaultP;
	ASSERT(MotorPid->I > MotorPidMinI && MotorPid->I < MotorPidMaxI);
	MotorPid->I = MotorPIDDefaultI;
	ASSERT(MotorPid->D > MotorPidMinD && MotorPid->D < MotorPidMaxD);
	MotorPid->D = MotorPIDDefaultD;
	tpm_pwm_init(TpmMotor, TpmMotorCh0, TpmMotorFreq, 0);
}

void MotorDutySet(int16 duty)
{
	ASSERT(duty > MotorSpeedMin && duty < MotorSpeedMax);//╤оят
	Speed->Expect = duty;
}
