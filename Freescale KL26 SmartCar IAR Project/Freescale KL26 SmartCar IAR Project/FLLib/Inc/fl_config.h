#include "common.h"
#include "fl_cfg.h"
#include "fl_eeprom.h"
#include "fl_ADC.h"
#include "fl_pid.h"
#include "fl_Motor.h"
#include "main.h"

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

#define ConfigLong (sizeof(FreeScaleCarConfig_s) / sizeof(uint8))

#define ConfigEndDefault 0x00
#define ConfigEnd 0xff

struct  ConfigPid_s
{
#if UseCheck
	uint8 PidStart;
#endif // UseCheck
	struct Pid_s Pid;
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
	struct MotorSpeed_s Speed;
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
	SteerDeviationDegree_e Domain;//Ä£ºý¿ØÖÆÂÛÓò
#if UseCheck
	uint8 SteerEnd;
#endif // UseCheck
};

struct ConfigAdcNom_s
{
#if UseCheck
	uint8 AdcStart;
#endif // UseCheck
	struct FLAdc_s Adc;
#if UseCheck
	uint8 AdcEnd;
#endif // UseCheck
};

typedef enum 
{
	CarStandby,
	CarRunning,
	CarFinish,
}CarState_e;

struct Config_s 
{
#if UseCheck
	uint8 ConfigStart;
#endif // UseCheck
	struct ConfigAdcNom_s AdcNormalMax;
	struct ConfigAdcNom_s AdcNormalMin;
	struct ConfigSteer Steer;
	struct ConfigMotor_s Motor;
	CarState_e CarState;
#if UseCheck
	uint8 ConfigEnd;
#endif // UseCheck
};

typedef struct 
{
	uint8 WhoAmI;
	struct Config_s Config;
	uint8 EepromConfigEnd;//default == 0
}FreeScaleCarConfig_s;

extern FreeScaleCarConfig_s FreecaleConfig;

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
	ConfigAllGreen,
	ConfigWhoAmIError,
	ConfigLostEnd,

	ConfigOthers
}ConfigErrorType_s;

ConfigErrorType_s ConfigWrite(FreeScaleCarConfig_s * config);
ConfigErrorType_s ConfigRead(FreeScaleCarConfig_s * config);

ConfigErrorType_s ConfigBackUp(FreeScaleCarConfig_s * config, ConfigBackNum_e backUpNum);
ConfigErrorType_s ConfigRecovery(FreeScaleCarConfig_s * config, ConfigBackNum_e backUpNum);
ConfigErrorType_s ConfigBackUpClear(ConfigBackNum_e backUpNum);

ConfigErrorType_s ConfigSendOverUart(FreeScaleCarConfig_s * eeppromConfig);
ConfigErrorType_s ConfigFormat(FreeScaleCarConfig_s * config, char * str);
ConfigErrorType_s ConfigShowOnLcd(FreeScaleCarConfig_s config);

ConfigErrorType_s ConfigSetDefaultInEeprom();
#endif//_FL_config_
