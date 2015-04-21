#include "fl_config.h"

ConfigErrorType_s ConfigWrite(FreeScaleCarConfig_s * eepromConfig)
{
	uint16 eepRomAddress = 0x0000;
	assert(eepromConfig->WhoAmI != CONFIG_WHO_AM_I);
	//while (eepromConfig->EepromConfigEnd != ConfigEnd)
	while (((uint8*)eepromConfig + eepRomAddress) != ((uint8*)(eepromConfig->EepromConfigEnd)))
	{
		EepromWrite(eepRomAddress++,*(((uint8*)eepromConfig) + eepRomAddress));
		assert(eepRomAddress >= ConfigLong);
	}
	return AllGreen;
}

ConfigErrorType_s ConfigRead(FreeScaleCarConfig_s * eepromConfig)
{
	uint16 eepRomAddress = 0x0000;
	eepromConfig->EepromConfigEnd = 0x0000;
	//while ((eepromConfig->EepromConfigEnd) != ConfigEnd)
	while (((uint8*)eepromConfig + eepRomAddress) != ((uint8*)(eepromConfig->EepromConfigEnd)))
	{
		*((uint8*)eepromConfig + eepRomAddress) = EepromRead(eepRomAddress++);
		if (eepRomAddress >= ConfigLong)
		{
			return LostEnd;
		}
	}
	if (eepromConfig->WhoAmI != CONFIG_WHO_AM_I)
	{
		return WhoAmIError;
	}
	return AllGreen;
}

ConfigErrorType_s ConfigBackUp(FreeScaleCarConfig_s * eepromConfig, ConfigBackNum_e backUpNum)
{
	assert(backUpNum == BackUp_All);
	uint16 eepRomAddress = 0x0000 + ConfigLong * (uint8)backUpNum;
	assert(eepromConfig->WhoAmI != CONFIG_WHO_AM_I);
	//while (eepromConfig->EepromConfigEnd != ConfigEnd)
	while (((uint8*)eepromConfig + eepRomAddress) != ((uint8*)(eepromConfig->EepromConfigEnd)))
	{
		EepromWrite(eepRomAddress++, *(((uint8*)eepromConfig) + eepRomAddress));
		assert(eepRomAddress >= ConfigLong);
	}
	return AllGreen;
}
ConfigErrorType_s ConfigRecovery(FreeScaleCarConfig_s * eepromConfig, ConfigBackNum_e backUpNum)
{
	assert(backUpNum == BackUp_All);
	uint16 eepRomAddress = 0x0000 + ConfigLong * (uint8)backUpNum;
	eepromConfig->EepromConfigEnd = 0x0000;
	//while ((eepromConfig->EepromConfigEnd) != ConfigEnd)
	while (((uint8*)eepromConfig + eepRomAddress) != ((uint8*)(eepromConfig->EepromConfigEnd)))
	{
		*((uint8*)eepromConfig + eepRomAddress) = EepromRead(eepRomAddress++);
		if (eepRomAddress >= ConfigLong)
		{
			return LostEnd;
		}
	}
	if (eepromConfig->WhoAmI != CONFIG_WHO_AM_I)
	{
		return WhoAmIError;
	}
	return AllGreen;
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
	return AllGreen;
}

/*参数格式化
数据顺序：

adc0,1,2,3
电机pid
期望车速
舵机pid
*/
ConfigErrorType_s ConfigFormat(FreeScaleCarConfig_s * eepromConfig,char * str)
{
	ASSERT(eepromConfig->WhoAmI != CONFIG_WHO_AM_I);
	if (eepromConfig->WhoAmI != CONFIG_WHO_AM_I)
	{
		return WhoAmIError;
	}
	ASSERT(eepromConfig->EepromConfigEnd != ConfigEnd);
	if (eepromConfig->EepromConfigEnd != ConfigEnd)
	{
		return LostEnd;
	}

	sprintf(str,
		"$%d,%d,%d,%d|%d,%d,%d|%d|%d,%d,%d#",
		eepromConfig->Config.AdcNormalMax.Adc.FLAdc0,
		eepromConfig->Config.AdcNormalMax.Adc.FlAdc1,
		eepromConfig->Config.AdcNormalMax.Adc.FLAdc2,
		eepromConfig->Config.AdcNormalMax.Adc.FLAdc3,
		eepromConfig->Config.Motor.Pid.Pid.P,
		eepromConfig->Config.Motor.Pid.Pid.I,
		eepromConfig->Config.Motor.Pid.Pid.D,
		eepromConfig->Config.Motor.Speed,
		eepromConfig->Config.Steer.Pid.Pid.P,
		eepromConfig->Config.Steer.Pid.Pid.I,
		eepromConfig->Config.Steer.Pid.Pid.D
		);

	return AllGreen;
}

ConfigErrorType_s ConfigShowOnLcd(FreeScaleCarConfig_s eepromConfig)
{
	//TODO:
	ASSERT(true);
	return Others;
}

ConfigErrorType_s ConfigSendOverUart(FreeScaleCarConfig_s * eepromConfig)
{
	ASSERT(eepromConfig->WhoAmI != CONFIG_WHO_AM_I);
	if (eepromConfig->WhoAmI != CONFIG_WHO_AM_I)
	{
		return WhoAmIError;
	}
	ASSERT(eepromConfig->EepromConfigEnd != ConfigEnd);
	if (eepromConfig->EepromConfigEnd != ConfigEnd)
	{
		return LostEnd;
	}

	printf(
		"$%d,%d,%d,%d|%d,%d,%d|%d|%d,%d,%d#",
		eepromConfig->Config.AdcNormalMax.Adc.FLAdc0,
		eepromConfig->Config.AdcNormalMax.Adc.FlAdc1,
		eepromConfig->Config.AdcNormalMax.Adc.FLAdc2,
		eepromConfig->Config.AdcNormalMax.Adc.FLAdc3,
		eepromConfig->Config.Motor.Pid.Pid.P,
		eepromConfig->Config.Motor.Pid.Pid.I,
		eepromConfig->Config.Motor.Pid.Pid.D,
		eepromConfig->Config.Motor.Speed,
		eepromConfig->Config.Steer.Pid.Pid.P,
		eepromConfig->Config.Steer.Pid.Pid.I,
		eepromConfig->Config.Steer.Pid.Pid.D
		);

	return AllGreen;
}

