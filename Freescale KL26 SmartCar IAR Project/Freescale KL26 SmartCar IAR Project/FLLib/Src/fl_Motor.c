#include "fl_motor.h"

//struct Pid_s  MotorPid;
struct MotorSpeed_s Speed = { 0, 0 };

//void MotorPidSet(struct Pid_s * pid)
//{
//	ASSERT(pid.P > MotorPidMinP && pid.P < MotorPidMaxP);
//	ASSERT(pid.I > MotorPidMinI && pid.I < MotorPidMaxI);
//	ASSERT(pid.D > MotorPidMinD && pid.D < MotorPidMaxD);
//	MotorPid = pid;
//}


void MotorInit()
{
	tpm_pwm_init(TpmMotor, TpmMotorCh0, TpmMotorFreq, 0);
	tpm_pwm_init(TpmMotor, TpmMotorCh1, TpmMotorFreq, 0);
}
