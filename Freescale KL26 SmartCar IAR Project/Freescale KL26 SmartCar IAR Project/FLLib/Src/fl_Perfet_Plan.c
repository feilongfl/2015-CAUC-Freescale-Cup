#include "fl_Perfet_Plan.h"


uint16 PerfetPlan = 0;



FreeScaleCarConfig_s PerfetConfig[CarNum][PlanNum];

void PerfetInit()
{
	/************************************************************************/
	/*                        init                                       */
	/************************************************************************/
	for (uint8 i = 0; i < CarNum;i++)
	{
		for (uint8 j = 0; j < PlanNum; j++)
		{
			uint8 * configAdd = (uint8 *)&PerfetConfig[i][j];
			uint16 eepRomAddress = 0x0000;
			while (eepRomAddress < ConfigLong)
			{
				*(configAdd + eepRomAddress++) = 0x00;
			}
		}
	}
	/************************************************************************/
	/*                      car1                                         */
	/************************************************************************/
	//////////////////////////////////////////////////////////////////////////
	PerfetConfig[Car1 - 1][0].WhoAmI = CONFIG_WHO_AM_I;

	PerfetConfig[Car1 - 1][0].Config.AdcNormalMax.Adc.FLAdc0 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMax.Adc.FlAdc1 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMax.Adc.FLAdc2 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMax.Adc.FLAdc3 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMax.Adc.AdcVertical.Adc0 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMax.Adc.AdcVertical.Adc1 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMin.Adc.FLAdc0 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMin.Adc.FlAdc1 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMin.Adc.FLAdc2 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMin.Adc.FLAdc3 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMin.Adc.AdcVertical.Adc0 = 150u;
	PerfetConfig[Car1 - 1][0].Config.AdcNormalMin.Adc.AdcVertical.Adc1 = 150u;
	PerfetConfig[Car1 - 1][0].Config.LostAdcMin = 550;
	PerfetConfig[Car1 - 1][0].Config.LostAdcVerticalMin = 70;
	PerfetConfig[Car1 - 1][0].Config.Steer.Pid.Pid.P = 50;
	PerfetConfig[Car1 - 1][0].Config.Steer.Pid.Pid.I = 0;
	PerfetConfig[Car1 - 1][0].Config.Steer.Pid.Pid.D = 17;
	PerfetConfig[Car1 - 1][0].Config.Steer.AdcDomain = 40;
	PerfetConfig[Car1 - 1][0].Config.Steer.SteerDomainDif = 105;
	PerfetConfig[Car1 - 1][0].Config.Steer.SteerCtrlMethod = SteerCtrlMethod_Fuzzy;
	PerfetConfig[Car1 - 1][0].Config.Motor.Pid.Pid.P = 70;
	PerfetConfig[Car1 - 1][0].Config.Motor.Pid.Pid.I = 4;
	PerfetConfig[Car1 - 1][0].Config.Motor.Pid.Pid.D = 10;
	PerfetConfig[Car1 - 1][0].Config.Motor.Speed.LineSpeed = 670;
	PerfetConfig[Car1 - 1][0].Config.Motor.Speed.TurnSpeed = 550;
	PerfetConfig[Car1 - 1][0].Config.Motor.Speed.LostLineSpeed = 400;
	PerfetConfig[Car1 - 1][0].Config.CarState = CarStandby;

	PerfetConfig[Car1 - 1][0].EepromConfigEnd = ConfigEnd;


	/************************************************************************/
	/*                         car2                                  */
	/************************************************************************/
}

void CarToPerfet()
{
	LCDPrintInverse(LcdTitleLocal, LcdTitleLine, (unsigned char *)"RUNNING...     ");
	PerfetInit();

	if (ConfigWrite(&PerfetConfig[FreecaleConfig.Config.CarThis][PerfetPlan]) != ConfigAllGreen)
	{
		LcdErrShow(SettingErrFail);
	}
	else
	{
		LcdCls();
		LCDPrintInverse(LcdTitleLocal, LcdTitleLine, (unsigned char *)"DONE.");
		LCDPrint(LcdLocal1, LcdLine3, (unsigned char *)"Please Reboot!");
		while (1);
	}
}
