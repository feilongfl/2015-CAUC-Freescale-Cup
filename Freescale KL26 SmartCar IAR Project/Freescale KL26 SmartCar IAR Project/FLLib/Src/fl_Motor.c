#include "fl_motor.h"


struct Pid_s MotorPid = {
	MotorPIDDefaultP,
	MotorPIDDefaultI,
	MotorPIDDefaultD,
};//电机当前Pid参数
struct Pid_s * MotorPidAddress = &MotorPid;
