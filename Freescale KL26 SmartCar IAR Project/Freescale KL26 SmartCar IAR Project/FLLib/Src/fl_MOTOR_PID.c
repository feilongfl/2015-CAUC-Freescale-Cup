#include "fl_MOTOR_PID.h"

struct Pid_s Motorpid;
extern struct MotorSpeed_s Speed;

int32 MotorCtrlUsePid()
{
	Motorpid.Now = Speed.Acturally;
	Motorpid.Target = Speed.Expect;

	return PID(&Motorpid);
}

uint32 mpwm = 0;

void MotorCtrl()
{
	mpwm += MotorCtrlUsePid() / 100;
	if (mpwm > 4000)
	{
		mpwm = 4000;
	}
	tpm_pwm_duty(TpmMotor, TpmMotorCh0, mpwm);
	
}

void MotorPidInit()
{
	Motorpid.Target = 0;

	Motorpid.g = 0;
	Motorpid.Imax = 0;
	Motorpid.Integral = 0;
	Motorpid.last_error = 0;
	Motorpid.Now = 0;

	Motorpid.P = MotorPIDDefaultP;
	Motorpid.I = MotorPIDDefaultI;
	Motorpid.D = MotorPIDDefaultD;
}