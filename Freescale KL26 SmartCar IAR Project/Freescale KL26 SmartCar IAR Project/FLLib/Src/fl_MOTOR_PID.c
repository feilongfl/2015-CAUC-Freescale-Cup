#include "fl_MOTOR_PID.h"
#include "fl_config.h"

//struct Pid_s FreecaleConfig.Config.Motor.Pid.Pid;


int32 MotorCtrlUsePid()
{
	FreecaleConfig.Config.Motor.Pid.Pid.Now = Speed.Acturally;
	FreecaleConfig.Config.Motor.Pid.Pid.Target = Speed.Expect;
	
	return PID(&FreecaleConfig.Config.Motor.Pid.Pid);
}

int32 mpwm = 0;

void MotorCtrl()
{
  uint8 a = MotorCtrlUsePid();
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
	FreecaleConfig.Config.Motor.Pid.Pid.Target = 0;

	FreecaleConfig.Config.Motor.Pid.Pid.g = 0;
	FreecaleConfig.Config.Motor.Pid.Pid.Imax = 0;
	FreecaleConfig.Config.Motor.Pid.Pid.Integral = 0;
	FreecaleConfig.Config.Motor.Pid.Pid.last_error = 0;
	FreecaleConfig.Config.Motor.Pid.Pid.Now = 0;

	FreecaleConfig.Config.Motor.Pid.Pid.P = MotorPIDDefaultP;
	FreecaleConfig.Config.Motor.Pid.Pid.I = MotorPIDDefaultI;
	FreecaleConfig.Config.Motor.Pid.Pid.D = MotorPIDDefaultD;
}


void MotorPidSetP(int16 p)
{
	ASSERT(p > MotorPidMinP && p < MotorPidMaxP);
	FreecaleConfig.Config.Motor.Pid.Pid.P = p;
}

void MotorPidSetI(int16 i)
{
	ASSERT(i > MotorPidMinI && i < MotorPidMaxI);
	FreecaleConfig.Config.Motor.Pid.Pid.I = i;
}

void MotorPidSetD(int16 d)
{
	ASSERT(d > MotorPidMinD && d < MotorPidMaxD);
	FreecaleConfig.Config.Motor.Pid.Pid.D = d;
}

