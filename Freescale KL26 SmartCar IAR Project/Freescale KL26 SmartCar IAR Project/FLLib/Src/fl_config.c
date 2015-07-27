#include "fl_config.h"
FreeScaleCarConfig_s FreecaleConfig;

ConfigErrorType_s ConfigInit()
{
	EepromInit();
	while (true)
	{
		if (ConfigRead(&FreecaleConfig) != ConfigAllGreen)
		{
			printf("config error!\n");
			ASSERT(ConfigSetDefaultInEeprom() == ConfigAllGreen);//eeprom失败
			printf("config set default!\n\nplease restart!\n");
			while (1);
		}
		else
		{
			break;
		}
	}

	if (FreecaleConfig.Config.CarState == CarFinish)
	{
		FreecaleConfig.Config.CarState = CarStandby;
		ConfigWrite(&FreecaleConfig);
	}

	return ConfigAllGreen;
}

ConfigErrorType_s ConfigWrite(FreeScaleCarConfig_s * config)
{
	uint16 eepRomAddress = 0x0000;
	ASSERT(config->WhoAmI == CONFIG_WHO_AM_I);
	//while (config->EepromConfigEnd != ConfigEnd)
	while (eepRomAddress <= ConfigLong)
	{
		EepromWrite(eepRomAddress++,(uint8)*(((uint8*)config) + eepRomAddress));
	}
	
	return ConfigAllGreen;
}

ConfigErrorType_s ConfigRead(FreeScaleCarConfig_s * config)
{
	uint16 eepRomAddress = 0x0000;
	config->EepromConfigEnd = 0x0000;
	//while ((config->EepromConfigEnd) != ConfigEnd)
	while (eepRomAddress <= ConfigLong)
	{
		*((uint8*)config + eepRomAddress ++ ) = EepromRead(eepRomAddress);
	}
	if (config->WhoAmI != CONFIG_WHO_AM_I)
	{
		return ConfigWhoAmIError;
	}
	return ConfigAllGreen;
}

ConfigErrorType_s ConfigBackUp(FreeScaleCarConfig_s * config, ConfigBackNum_e backUpNum)
{
	ASSERT(backUpNum == BackUp_All);
	uint16 eepRomAddress = 0x0000 + ConfigLong * (uint8)backUpNum;
	ASSERT(config->WhoAmI != CONFIG_WHO_AM_I);
	//while (config->EepromConfigEnd != ConfigEnd)
	while (((uint8*)config + eepRomAddress) != ((uint8*)(config->EepromConfigEnd)))
	{
		EepromWrite(eepRomAddress++, *(((uint8*)config) + eepRomAddress));
		ASSERT(eepRomAddress >= ConfigLong);
	}
	return ConfigAllGreen;
}
ConfigErrorType_s ConfigRecovery(FreeScaleCarConfig_s * config, ConfigBackNum_e backUpNum)
{
	ASSERT(backUpNum == BackUp_All);
	uint16 eepRomAddress = 0x0000 + ConfigLong * (uint8)backUpNum;
	config->EepromConfigEnd = 0x0000;
	//while ((config->EepromConfigEnd) != ConfigEnd)
	while (((uint8*)config + eepRomAddress) != ((uint8*)(config->EepromConfigEnd)))
	{
		*((uint8*)config + eepRomAddress) = EepromRead(eepRomAddress++);
		if (eepRomAddress >= ConfigLong)
		{
			return ConfigLostEnd;
		}
	}
	if (config->WhoAmI != CONFIG_WHO_AM_I)
	{
		return ConfigWhoAmIError;
	}
	return ConfigAllGreen;
}

ConfigErrorType_s ConfigBackUpClear(ConfigBackNum_e backUpNum)
{
	if (backUpNum == BackUp_All)
	{
		for (uint8 i = 0; i < BackUp_All;i++)
		{
			ConfigBackUpClear((ConfigBackNum_e)i);
		}
	}
	else
	{
		uint16 eepRomAddress = 0x0000 + ConfigLong * (uint8)backUpNum;
		while (eepRomAddress < ConfigLong)
		{
			EepromWrite(eepRomAddress++, 0x00);
		}
	}
	return ConfigAllGreen;
}

/*参数格式化
数据顺序：

adc0,1,2,3
电机pid
期望车速
舵机pid
车状态
*/
ConfigErrorType_s ConfigFormat(FreeScaleCarConfig_s * config,char * str)
{
	ASSERT(config->WhoAmI != CONFIG_WHO_AM_I);
	if (config->WhoAmI != CONFIG_WHO_AM_I)
	{
		return ConfigWhoAmIError;
	}
	ASSERT(config->EepromConfigEnd != ConfigEnd);
	if (config->EepromConfigEnd != ConfigEnd)
	{
		return ConfigLostEnd;
	}

	sprintf(str,
		"$%d,%d,%d,%d|%d,%d,%d|%d,%d|%d,%d,%d#",
		config->Config.AdcNormalMax.Adc.FLAdc0,
		config->Config.AdcNormalMax.Adc.FlAdc1,
		config->Config.AdcNormalMax.Adc.FLAdc2,
		config->Config.AdcNormalMax.Adc.FLAdc3,
		config->Config.Motor.Pid.Pid.P,
		config->Config.Motor.Pid.Pid.I,
		config->Config.Motor.Pid.Pid.D,
		config->Config.Motor.Speed.Acturally,
		config->Config.Motor.Speed.Expect,
		config->Config.Steer.Pid.Pid.P,
		config->Config.Steer.Pid.Pid.I,
		config->Config.Steer.Pid.Pid.D,
		config->Config.CarState
		);

	return ConfigAllGreen;
}

ConfigErrorType_s ConfigShowOnLcd(FreeScaleCarConfig_s config)
{
	//TODO:
	ASSERT(true);
	return ConfigOthers;
}

ConfigErrorType_s ConfigSendOverUart(FreeScaleCarConfig_s * config)
{
	ASSERT(config->WhoAmI != CONFIG_WHO_AM_I);
	if (config->WhoAmI != CONFIG_WHO_AM_I)
	{
		return ConfigWhoAmIError;
	}
	ASSERT(config->EepromConfigEnd != ConfigEnd);
	if (config->EepromConfigEnd != ConfigEnd)
	{
		return ConfigLostEnd;
	}

	printf(
		"$%d,%d,%d,%d|%d,%d,%d|%d,%d|%d,%d,%d#",
		config->Config.AdcNormalMax.Adc.FLAdc0,
		config->Config.AdcNormalMax.Adc.FlAdc1,
		config->Config.AdcNormalMax.Adc.FLAdc2,
		config->Config.AdcNormalMax.Adc.FLAdc3,
		config->Config.Motor.Pid.Pid.P,
		config->Config.Motor.Pid.Pid.I,
		config->Config.Motor.Pid.Pid.D,
		config->Config.Motor.Speed.Acturally,
		config->Config.Motor.Speed.Expect,
		config->Config.Steer.Pid.Pid.P,
		config->Config.Steer.Pid.Pid.I,
		config->Config.Steer.Pid.Pid.D,
		config->Config.CarState
		);

	return ConfigAllGreen;
}

ConfigErrorType_s ConfigSetDefaultInEeprom()
{
	FreeScaleCarConfig_s config;
    uint8 * configAdd = (uint8 *)&config;
    uint16 eepRomAddress = 0x0000;
    while (eepRomAddress < ConfigLong)
	{
		*(configAdd +eepRomAddress++) = 0x00;
	}

	config.WhoAmI = CONFIG_WHO_AM_I;

	config.Config.AdcNormalMax.Adc.FLAdc0 = 150u;
	config.Config.AdcNormalMax.Adc.FlAdc1 = 150u;
	config.Config.AdcNormalMax.Adc.FLAdc2 = 150u;
	config.Config.AdcNormalMax.Adc.FLAdc3 = 150u;
	config.Config.AdcNormalMax.Adc.AdcVertical.Adc0 = 150u;
	config.Config.AdcNormalMax.Adc.AdcVertical.Adc1 = 150u;

	config.Config.AdcNormalMin.Adc.FLAdc0 = 150u;
	config.Config.AdcNormalMin.Adc.FlAdc1 = 150u;
	config.Config.AdcNormalMin.Adc.FLAdc2 = 150u;
	config.Config.AdcNormalMin.Adc.FLAdc3 = 150u;
	config.Config.AdcNormalMin.Adc.AdcVertical.Adc0 = 150u;
	config.Config.AdcNormalMin.Adc.AdcVertical.Adc1 = 150u;

	config.Config.Motor.Speed.Acturally = 0;
	config.Config.Motor.Speed.Expect = 10;
	config.Config.Motor.Speed.LineSpeed = 1000;
	config.Config.Motor.Speed.TurnSpeed = 700;
	config.Config.Motor.Speed.LineSpeed = 500;

#include "fl_MOTOR_PID.h"

	config.Config.Motor.Pid.Pid.P = MotorPIDDefaultP;
	config.Config.Motor.Pid.Pid.I = MotorPIDDefaultI;
	config.Config.Motor.Pid.Pid.D = MotorPIDDefaultD;

#include "fl_steer_pid.h"
	config.Config.Steer.Pid.Pid.P = SteerPIDDefaultP;
	config.Config.Steer.Pid.Pid.I = SteerPIDDefaultI;
	config.Config.Steer.Pid.Pid.D = SteerPIDDefaultD;
	config.Config.Steer.AdcDomain = (SteerDeviationDegree_e)90;

	config.Config.CarState = CarStandby;

	config.EepromConfigEnd = ConfigEnd;

	return ConfigWrite(&config);
}
