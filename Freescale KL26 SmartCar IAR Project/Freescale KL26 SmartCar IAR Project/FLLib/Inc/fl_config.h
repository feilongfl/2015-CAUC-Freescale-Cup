#include "common.h"
#include "fl_cfg.h"

#ifndef _FL_config_
#define _FL_config_

#define Use		1
#define NotUse	0
#define UseCheck NotUse

#define WHO_AM_I 0x42;

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

struct EepromConfig_s 
{
	uint8 WhoAmI;
	struct Config_s Config;
	uint8 EepromConfigEnd;
};

#endif//_FL_config_
