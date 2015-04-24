#include "fl_config.h"

ConfigErrorType_s ConfigWrite(FreeScaleCarConfig_s * config)
{
	uint16 eepRomAddress = 0x0000;
	assert(config->WhoAmI != CONFIG_WHO_AM_I);
	//while (config->EepromConfigEnd != ConfigEnd)
	while (((uint8*)config + eepRomAddress) != ((uint8*)(config->EepromConfigEnd)))
	{
		EepromWrite(eepRomAddress++,*(((uint8*)config) + eepRomAddress));
		assert(eepRomAddress >= ConfigLong);
	}
	return ConfigAllGreen;
}

ConfigErrorType_s ConfigRead(FreeScaleCarConfig_s * config)
{
	uint16 eepRomAddress = 0x0000;
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

ConfigErrorType_s ConfigBackUp(FreeScaleCarConfig_s * config, ConfigBackNum_e backUpNum)
{
	assert(backUpNum == BackUp_All);
	uint16 eepRomAddress = 0x0000 + ConfigLong * (uint8)backUpNum;
	assert(config->WhoAmI != CONFIG_WHO_AM_I);
	//while (config->EepromConfigEnd != ConfigEnd)
	while (((uint8*)config + eepRomAddress) != ((uint8*)(config->EepromConfigEnd)))
	{
		EepromWrite(eepRomAddress++, *(((uint8*)config) + eepRomAddress));
		assert(eepRomAddress >= ConfigLong);
	}
	return ConfigAllGreen;
}
ConfigErrorType_s ConfigRecovery(FreeScaleCarConfig_s * config, ConfigBackNum_e backUpNum)
{
	assert(backUpNum == BackUp_All);
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
		"$%d,%d,%d,%d|%d,%d,%d|%d|%d,%d,%d#",
		config->Config.AdcNormalMax.Adc.FLAdc0,
		config->Config.AdcNormalMax.Adc.FlAdc1,
		config->Config.AdcNormalMax.Adc.FLAdc2,
		config->Config.AdcNormalMax.Adc.FLAdc3,
		config->Config.Motor.Pid.Pid.P,
		config->Config.Motor.Pid.Pid.I,
		config->Config.Motor.Pid.Pid.D,
		config->Config.Motor.Speed,
		config->Config.Steer.Pid.Pid.P,
		config->Config.Steer.Pid.Pid.I,
		config->Config.Steer.Pid.Pid.D
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
		"$%d,%d,%d,%d|%d,%d,%d|%d|%d,%d,%d#",
		config->Config.AdcNormalMax.Adc.FLAdc0,
		config->Config.AdcNormalMax.Adc.FlAdc1,
		config->Config.AdcNormalMax.Adc.FLAdc2,
		config->Config.AdcNormalMax.Adc.FLAdc3,
		config->Config.Motor.Pid.Pid.P,
		config->Config.Motor.Pid.Pid.I,
		config->Config.Motor.Pid.Pid.D,
		config->Config.Motor.Speed,
		config->Config.Steer.Pid.Pid.P,
		config->Config.Steer.Pid.Pid.I,
		config->Config.Steer.Pid.Pid.D
		);

	return ConfigAllGreen;
}

