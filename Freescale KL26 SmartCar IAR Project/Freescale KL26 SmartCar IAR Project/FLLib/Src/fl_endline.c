#include "fl_endline.h"
#include "fl_Motor.h"
#include "fl_config.h"


//////////////////////////////////////////////////////////////////////////
//÷’µ„œﬂ≈–∂œ≥Ã–Ú
//////////////////////////////////////////////////////////////////////////
void EndLine()
{
	if (key_check(Key_EndLine) != KEY_DOWN)
	{
		return;
	}
	else
	{
		switch (FreecaleConfig.Config.CarState)
		{
		case CarStandby:
			FreecaleConfig.Config.CarState = CarRunning;
			ConfigWrite(&FreecaleConfig);
			break;

		case CarRunning:
			FreecaleConfig.Config.CarState = CarFinish;
			ConfigWrite(&FreecaleConfig);
			break;

		case CarFinish:
			break;

		default:
			ASSERT(true);
			break;
		}
		Speed.Expect = 0;
	}
}
