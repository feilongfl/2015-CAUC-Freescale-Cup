#include "common.h"
#include "fl_cfg.h"
#include "fl_eeprom.h"

#ifndef _FL_config_
#define _FL_config_

#define Use		1
#define NotUse	0
#define UseCheck NotUse

#define CONFIG_WHO_AM_I 0x42
#define PidCheck 0x43
#define MotorCheck 0x44
#define SteerCheck 0x45
#define AdcCheck 0x46

#define ConfigLong 100

#define ConfigEndDefault 0x00
#define ConfigEnd 0xff

struct  ConfigPid_s
{
#if UseCheck
	uint8 PidStart;
#endif // UseCheck
	uint16 P;
	uint16 I;
	uint16 D;
#if UseCheck
	uint8 PidStop;
#endif // UseCheck
};

struct ConfigMotor_s
{
#if UseCheck
	uint8 MotorStart;
#endif // UseCheck
	struct ConfigPid_s Pid;
	uint16 Speed;
#if UseCheck
	uint8 MotorEnd;
#endif // UseCheck
};

struct ConfigSteer 
{
#if UseCheck
	uint8 SteerStart;
#endif // UseCheck
	struct ConfigPid_s Pid;
#if UseCheck
	uint8 SteerEnd;
#endif // UseCheck
};

struct ConfigAdcNom_s
{
#if UseCheck
	uint8 AdcStart;
#endif // UseCheck
	uint16 Adc1;
	uint16 Adc2;
	uint16 Adc3;
	uint16 Adc4;
#if UseCheck
	uint8 AdcEnd;
#endif // UseCheck
};

struct Config_s 
{
#if UseCheck
	uint8 ConfigStart;
#endif // UseCheck
	struct ConfigAdcNom_s AdcNormalMax;
	struct ConfigPid_s;
#if UseCheck
	uint8 ConfigEnd;
#endif // UseCheck
};

typedef struct 
{
	uint8 WhoAmI;
	struct Config_s Config;
	uint8 EepromConfigEnd;//default == 0
}EepromConfig_s;

typedef enum 
{
	BackUp0,
	BackUp1,
	BackUp2,
	BackUp3,
	BackUp4,

	BackUp_All
}ConfigBackNum_e;

typedef enum 
{
	AllGreen,
	WhoAmIError,
	LostEnd,

	Others
}ConfigErrorType_s;

ConfigErrorType_s ConfigWrite(EepromConfig_s * eepromConfig);
ConfigErrorType_s ConfigRead(EepromConfig_s * eepromConfig);

ConfigErrorType_s ConfigBackUp(EepromConfig_s * eepromConfig, ConfigBackNum_e backUpNum);
ConfigErrorType_s ConfigRecovery(EepromConfig_s * eepromConfig, ConfigBackNum_e backUpNum);
ConfigErrorType_s ConfigBackUpClear(ConfigBackNum_e backUpNum);

#endif//_FL_config_
