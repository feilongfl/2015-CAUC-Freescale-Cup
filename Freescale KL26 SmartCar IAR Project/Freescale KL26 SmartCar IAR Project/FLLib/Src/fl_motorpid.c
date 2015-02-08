#include "fl_motorpid.h"


struct Pid_s MotorPid = {
	MotorPIDDefaultP,
	MotorPIDDefaultI,
	MotorPIDDefaultD,
};//电机当前Pid参数