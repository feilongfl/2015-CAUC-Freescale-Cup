#include "fl_config.h"

ConfigErrorType_s ConfigWrite(EepromConfig_s * eepromConfig)
{
	uint16 eepRomAddress = 0x0000;
	assert(eepromConfig->WhoAmI != CONFIG_WHO_AM_I);
	while (eepromConfig->EepromConfigEnd != ConfigEnd)
	{
		EepromWrite(eepRomAddress++,*(((uint8*)eepromConfig) + eepRomAddress));
		if (eepRomAddress >= ConfigLong)
		{
			break;
		}
	}
	return AllGreen;
}

ConfigErrorType_s ConfigRead(EepromConfig_s * eepromConfig)
{
	uint16 eepRomAddress = 0x0000;
	eepromConfig->EepromConfigEnd = 0x0000;
	while ((eepromConfig->EepromConfigEnd) != ConfigEnd)
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

ConfigErrorType_s ConfigBackUp(EepromConfig_s * eepromConfig, ConfigBackNum_e backUpNum)
{
	assert(backUpNum == BackUp_All);
	uint16 eepRomAddress = 0x0000 + ConfigLong * (uint8)backUpNum;
	assert(eepromConfig->WhoAmI != CONFIG_WHO_AM_I);
	while (eepromConfig->EepromConfigEnd != ConfigEnd)
	{
		EepromWrite(eepRomAddress++, *(((uint8*)eepromConfig) + eepRomAddress));
		if (eepRomAddress >= ConfigLong)
		{
			break;
		}
	}
	return AllGreen;
}
ConfigErrorType_s ConfigRecovery(EepromConfig_s * eepromConfig, ConfigBackNum_e backUpNum)
{
	assert(backUpNum == BackUp_All);
	uint16 eepRomAddress = 0x0000 + ConfigLong * (uint8)backUpNum;
	eepromConfig->EepromConfigEnd = 0x0000;
	while ((eepromConfig->EepromConfigEnd) != ConfigEnd)
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
}
