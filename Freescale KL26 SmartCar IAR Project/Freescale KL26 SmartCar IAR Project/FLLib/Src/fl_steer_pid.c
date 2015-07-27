#include "fl_steer_pid.h"
#include "fl_config.h"

struct Pid_s SteerPid;

void SteerPidInit()
{

	SteerPid.Target = 0;

	SteerPid.g = 0;
	SteerPid.Imax = 0;
	SteerPid.Integral = 0;
	SteerPid.last_error = 0;
	SteerPid.Now = 0;

	SteerPid.P = SteerPIDDefaultP;
	SteerPid.I = SteerPIDDefaultI;
	SteerPid.D = SteerPIDDefaultD;
}

int32 SteerCtrlUsePid(SteerDeviationDegree_e deviation)
{
	FreecaleConfig.Config.Steer.Pid.Pid.Now = deviation;

	return PID(&FreecaleConfig.Config.Steer.Pid.Pid);
}

