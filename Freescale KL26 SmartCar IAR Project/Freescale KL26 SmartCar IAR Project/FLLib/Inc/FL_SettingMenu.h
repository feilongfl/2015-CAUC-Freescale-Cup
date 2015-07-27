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
	//���˵�
	MenuMainMotor = 0,
	MenuMainSteer,
	MenuMainSpeed,
	MenuMainMode,
	MenuMainAdcNor,
	MenuMainReset,
	MenuMainItemNum,

	//����˵�
	MenuMotorKp = 0,
	MenuMotorKi,
	MenuMotorKd,
	MenuMotorItemNum,

	//����˵�
	MenuSteerKp = 0,
	MenuSteerKi,
	MenuSteerKd,
	MenuSteerAdcDomain,
	MenuSteerSteerDomain,
	MenuSteerMethod,
	MenuSteerItemNum,

	//�ٶȲ˵�
	MenuSpeedLine = 0,
	MenuSpeedTurn,
	MenuSpeedLost,
	MenuSpeedItemNum,

	//����
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
/* �˳�                                                                 */
/************************************************************************/
//void SettingMenuQuit();


/************************************************************************/
/* �˵��б�                                                             */
/************************************************************************/
#define MenuTitle (unsigned char *)"SmartCarMenu"//�˵����ֵĹ�

/************************************************************************/
/* ��ʼ��                                                               */
/************************************************************************/
void SettingMenuInit();

#endif//_FL_SETTINGMENU_
