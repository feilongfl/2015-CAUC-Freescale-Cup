#include "common.h"
#include "fl_Olcd.h"
#include "FL_Key.h"

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
	//主菜单
	MenuMainMotor = 0,
	MenuMainSteer,
	MenuMainSpeed,
	MenuMainReset,

	//电机菜单
	MenuMotorKp = 0,
	MenuMotorKi,
	MenuMotorKd,
	MenuMotorReset,

	//舵机菜单
	MenuSteerKp = 0,
	MenuSteerKi,
	MenuSteerKd,
	MenuSteerReset,

	//速度菜单
	MenuSpeedSet = 0,
	MenuSpeedReset,

	//重置
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
/* 退出                                                                 */
/************************************************************************/
void SettingMenuQuit();


/************************************************************************/
/* 菜单位置控制                                                         */
/************************************************************************/
#define LcdTitleLocal 0//标题左边距
#define LcdMenuLocal 0//菜单左边距

#define LcdTitleLine LcdLine1//标题位置

#define LcdMenuLine1 LcdLine2//菜单位置
#define LcdMenuLine2 LcdLine3
#define LcdMenuLine3 LcdLine4

/************************************************************************/
/* 菜单列表                                                             */
/************************************************************************/
#define MenuTitle "SmartCarMenu"//菜单名字的哈

#define MainMenuItemNum 4
#define MotorMenuItemNum 4
#define SteerMenuItemNum 4
#define SpeedMenuItemNum 4
#define ResetMenuItemNum 3


typedef enum
{
	LcdErrOverMax,//超过最大值
	LcdErrOverMin,//超过最小值

	LcdErrKeyWrong,//当前界面不支持该按键

	LcdErrOther,//未定义错误

	LcdErrNumbers,//错误总数
}LcdErr_e;//错误号

#define LcdErrMsgLength 9//错误提示文字长度


/************************************************************************/
/* 菜单控制                                                             */
/************************************************************************/
void LcdMenuMove(MenuType_e menuType, MenuMove_e menuMove);
/************************************************************************/
/* 初始化                                                               */
/************************************************************************/
void SettingMenuInit();

/************************************************************************/
/* 显示                                                                 */
/************************************************************************/
void LcdShowMenu(MenuType_e menuType, MenuChoice_e menuChoice);//显示主菜单
void LcdShowMenu(MenuType_e menuType, MenuChoice_e menuChoice);//显示菜单（菜单类型，选中菜单）
void LcdShowMotorMenu(MenuChoice_e menuChoice);//显示电机设置菜单
void LcdErrShow(LcdErr_e lcdErr);

void MenuMainOperate();
#endif//_FL_SETTINGMENU_
