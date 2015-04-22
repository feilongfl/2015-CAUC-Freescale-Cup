#include "common.h"
#include "fl_cfg.h"
#include "fl_ADC.h"
#include "fl_Motor.h"
#include "Fl_steer.h"

#ifndef _FL_STATE_
#define _FL_STATE_

struct FreescaleCarState
{
	struct FLAdc_s Adc;
	struct MotorSpeed_s Speed;
	/*Pid_e Motor;
	Pid_e Steer;*/
};

typedef enum
{
	AllGreen,


	Others
}CarStateError_e;

//CarStateError_e CarStateGet();
CarStateError_e CarStateShowOnLcd();
CarStateError_e CarStateSendByUart();

#endif//_FL_State_
