#include "common.h"
#include "fl_Olcd.h"
#include "FL_Key.h"
#include "fl_error.h"

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
	MenuMainReset,

	//����˵�
	MenuMotorKp = 0,
	MenuMotorKi,
	MenuMotorKd,
	MenuMotorReset,

	//����˵�
	MenuSteerKp = 0,
	MenuSteerKi,
	MenuSteerKd,
	MenuSteerReset,

	//�ٶȲ˵�
	MenuSpeedSet = 0,
	MenuSpeedReset,

	//����
	MenuResetCancel1 = 0,
	MenuResetCancel2,
	MenuResetAccept,

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
void SettingMenuQuit();


/************************************************************************/
/* �˵�λ�ÿ���                                                         */
/************************************************************************/
#define LcdTitleLocal 0//������߾�
#define LcdMenuLocal 0//�˵���߾�

#define LcdTitleLine LcdLine1//����λ��

#define LcdMenuLine1 LcdLine2//�˵�λ��
#define LcdMenuLine2 LcdLine3
#define LcdMenuLine3 LcdLine4

/************************************************************************/
/* �˵��б�                                                             */
/************************************************************************/
#define MenuTitle "SmartCarMenu"//�˵����ֵĹ�

#define MainMenuItemNum 4
#define MotorMenuItemNum 4
#define SteerMenuItemNum 4
#define SpeedMenuItemNum 4
#define ResetMenuItemNum 3

/************************************************************************/
/* ��ʼ��                                                               */
/************************************************************************/
void SettingMenuInit();

#endif//_FL_SETTINGMENU_
