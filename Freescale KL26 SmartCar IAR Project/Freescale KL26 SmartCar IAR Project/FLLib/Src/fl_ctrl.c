#include "fl_ctrl.h"

void CarCtrl(Ctrl_e ctrl)
{
	switch (ctrl)
	{
	case Ctrl_Go:
		tpm_pwm_duty(TpmMotor, TpmMotorCh0, 10);
		SteerTurn(SteerDirectionCenter, 0);
		break;

	case Ctrl_GoLeft:
		break;

	case Ctrl_GoRight:
		break;

	case Ctrl_GoBack:
		break;

	case Ctrl_GoBackLeft:
		break;

	case Ctrl_GoBackRight:
		break;

	case Ctrl_Stop:
		tpm_pwm_duty(TpmMotor, TpmMotorCh0, 0);
		break;

	default:
		ASSERT(true);
		break;
	}
}