#include "fl_MOTOR_PID.h"

struct Pid_s MotorPid;


int32 MotorCtrlUsePid()
{
	MotorPid.Now = Speed.Acturally;
	MotorPid.Target = Speed.Expect;
	
	return PID(&MotorPid);
}

int32 mpwm = 0;

void MotorCtrl()
{
	mpwm += MotorCtrlUsePid() / 100;
	if (mpwm > 10000)
	{
		mpwm = 10000;
	}
	else if (mpwm < 0)
	{
		mpwm = 0;
	}
	printf("$%d,%d,%d,0,0,0,0,0#",Speed.Acturally,Speed.Expect,mpwm);
	tpm_pwm_duty(TpmMotor, TpmMotorCh0, (uint32)mpwm);

}

void MotorPidInit()
{
	MotorInit();
	MotorPid.Target = 0;

	MotorPid.g = 0;
	MotorPid.Imax = 0;
	MotorPid.Integral = 0;
	MotorPid.last_error = 0;
	MotorPid.Now = 0;

	MotorPid.P = MotorPIDDefaultP;
	MotorPid.I = MotorPIDDefaultI;
	MotorPid.D = MotorPIDDefaultD;
}


void MotorPidSetP(int16 p)
{
	ASSERT(p > MotorPidMinP && p < MotorPidMaxP);
	MotorPid.P = p;
}

void MotorPidSetI(int16 i)
{
	ASSERT(i > MotorPidMinI && i < MotorPidMaxI);
	MotorPid.I = i;
}

void MotorPidSetD(int16 d)
{
	ASSERT(d > MotorPidMinD && d < MotorPidMaxD);
	MotorPid.D = d;
}

