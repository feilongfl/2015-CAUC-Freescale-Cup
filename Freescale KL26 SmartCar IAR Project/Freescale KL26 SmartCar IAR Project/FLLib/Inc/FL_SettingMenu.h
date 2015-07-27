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
}MenuType_e;

typedef enum
{
	//���˵�
	MenuMainMotor = 0,
	MenuMainSteer,
	MenuMainSpeed,
	MenuMainAdcNor,
	MenuMainReset,
	MenuMainItemNum,

	//����˵�
	MenuMotorKp = 0,
	MenuMotorKi,
	MenuMotorKd,
	MenuMotorReset,
	MenuMotorItemNum,

	//����˵�
	MenuSteerAdcDomain = 0,
	MenuSteerSteerDomain,
	MenuSteerReserve,
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

}MenuChoice_e;

struct MenuChoice_s
{
	MenuChoice_e MainMenu;
	MenuChoice_e MotorMenu;
	MenuChoice_e SteerMenu;
	MenuChoice_e SpeedMenu;
	MenuChoice_e ResetMenu;
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
