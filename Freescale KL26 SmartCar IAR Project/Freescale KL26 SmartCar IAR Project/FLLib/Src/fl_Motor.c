#include "fl_motor.h"


struct Pid_s MotorPid = {
	MotorPIDDefaultP,
	MotorPIDDefaultI,
	MotorPIDDefaultD,
};//�����ǰPid����
struct Pid_s * MotorPidAddress = &MotorPid;
