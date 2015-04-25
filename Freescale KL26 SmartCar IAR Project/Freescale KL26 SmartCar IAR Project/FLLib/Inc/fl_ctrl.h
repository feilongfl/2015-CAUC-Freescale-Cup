#include "common.h"
#include "fl_cfg.h"
#include "fl_Motor.h"
#include "Fl_steer.h"

#ifndef _FL_ctrl_
#define _FL_ctrl_

typedef enum
{
	Ctrl_Go,
	Ctrl_GoLeft,
	Ctrl_GoRight,

	Ctrl_GoBack,
	Ctrl_GoBackLeft,
	Ctrl_GoBackRight,

	Ctrl_Stop,

	Ctrl_Max
}Ctrl_e;

#endif//_FL_ctrl_
