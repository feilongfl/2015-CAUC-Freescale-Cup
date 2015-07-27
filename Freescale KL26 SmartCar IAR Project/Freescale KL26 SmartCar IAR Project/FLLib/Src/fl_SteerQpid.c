#include "fl_SteerQpid.h"


qPID SteerQpid;

void SteerqPID_Init()
{

	// Configure settings
	SteerQpid.AntiWindup = ENABLED;
	SteerQpid.Bumpless = ENABLED;

	// Set mode to auotmatic (otherwise it will be in manual mode)
	SteerQpid.Mode = AUTOMATIC;

	// Configure de output limits for clamping
	SteerQpid.OutputMax = 1.0;
	SteerQpid.OutputMin = -1.0;

	// Set the rate at the PID will run in seconds
	SteerQpid.Ts = 0.005;

	// More settings
	SteerQpid.b = 1.0;
	SteerQpid.c = 1.0;

	// Init de controller
	SteerQpid.ctx.Ui_old = 0.0;
	SteerQpid.ctx.Ud_old = 0.0;
	SteerQpid.ctx.PV_old = 0.0;
	SteerQpid.ctx.SP_old = 0.0;

	// Set the tunning constants	
	SteerQpid.K = 0.5;
	SteerQpid.Ti = 1 / 0.02;
	SteerQpid.Td = 0.0;
	SteerQpid.Nd = 4.0;

}

// Update the PID and get the new output
// output = qPID_Procees(&controller, setPoint, sensor);
uint16 SteerqPIDCtrl()
{

}