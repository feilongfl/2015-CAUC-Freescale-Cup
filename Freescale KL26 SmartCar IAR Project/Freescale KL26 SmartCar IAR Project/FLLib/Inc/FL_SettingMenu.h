#include "common.h"
#include "fl_Olcd.h"
#include "FL_Key.h"
#include "fl_error.h"
#include "fl_config.h"

#ifndef _FL_SETTINGMENU_
#define _FL_SETTINGMENU_




//////////////////////////////////////////////////////////////////////////

typedef enum
{
	MoveUp,
	MoveDown,
}MenuMove_e;

typedef enum
{
	MenuMain,
	MenuMotor,
	MenuSteer,
	MenuSpeed,
	MenuReset,
	MenuMode,
}MenuType_e;

typedef enum
{
	//主菜单
	MenuMainMotor = 0,
	MenuMainSteer,
	MenuMainSpeed,
	MenuMainMode,
	MenuMainAdcNor,
	MenuMainReset,
	MenuMainItemNum,

	//电机菜单
	MenuMotorKp = 0,
	MenuMotorKi,
	MenuMotorKd,
	MenuMotorItemNum,

	//舵机菜单
	MenuSteerKp = 0,
	MenuSteerKi,
	MenuSteerKd,
	MenuSteerAdcDomain,
	MenuSteerSteerDomain,
	MenuSteerMethod,
	MenuSteerItemNum,

	//速度菜单
	MenuSpeedLine = 0,
	MenuSpeedTurn,
	MenuSpeedLost,
	MenuSpeedItemNum,

	//重置
	MenuResetCancel1 = 0,
	MenuResetCancel2,
	MenuResetAccept,
	MenuResetItemNum,

	//mode
	MenuModeEndLine = 0,
	MenuModePowerOnDelay,
	MenuModeMpu6050,
	MenuModeDistanceChangeSpeed,
	MenuModeNrf24l01,
	MenuModeNrfSendDistance,
	MenuModeNrfSendAdc,
	MenuModeMotorLowValid,
	MenuModeItemNum,

}MenuChoice_e;

struct MenuChoice_s
{
	MenuChoice_e MainMenu;
	MenuChoice_e MotorMenu;
	MenuChoice_e SteerMenu;
	MenuChoice_e SpeedMenu;
	MenuChoice_e ResetMenu;
	MenuChoice_e ModeMenu;
};


/************************************************************************/
/* 退出                                                                 */
/************************************************************************/
//void SettingMenuQuit();


/************************************************************************/
/* 菜单列表                                                             */
/************************************************************************/
#define MenuTitle (unsigned char *)"SmartCarMenu"//菜单名字的哈

/************************************************************************/
/* 初始化                                                               */
/************************************************************************/
void SettingMenuInit();

#endif//_FL_SETTINGMENU_
