
#include "FL_SettingMenu.h"
#include "FL_OLCD.h"
#include "fl_config.h"




const unsigned char * MainMenuItems[MenuMainItemNum] =
{
	"电机设置",
	"舵机设置",
	"车速设置",
	"归一化",
	"Reset EepRom",
};

const unsigned char * MotorMenuItems[MenuMotorItemNum] =
{
	"电机Kp",
	"电机Ki",
	"电机Kd",
	"重置电机",
};

const unsigned char * SteerMenuItems[MenuSteerItemNum] =
{
	"Adc Domain",
	"Steer Domain"
};

const unsigned char * SpeedMenuItems[MenuSpeedItemNum] =
{
	"LineSpeed",
	"TurnSpeed",
	"LostLineSpeed",
};

const unsigned char * ResetMenuItems[MenuResetItemNum] =
{
	"取消",
	"取消",
	"确认重置",
};

struct MenuChoice_s MenuChoice = { 
	(MenuChoice_e)0,
	(MenuChoice_e)0,
	(MenuChoice_e)0,
	(MenuChoice_e)0
};
struct MenuChoice_s * MenuChoiceAddress = &MenuChoice;


/************************************************************************/
/* 静态函数声明                                                                     */
/************************************************************************/

static void LcdShowMainMenu(MenuChoice_e menuChoice);
static void LcdShowMotorMenu(MenuChoice_e menuChoice);
static void LcdShowSteerMenu(MenuChoice_e menuChoice);
static void LcdShowSpeedMenu(MenuChoice_e menuChoice);
static void LcdShowResetMenu(MenuChoice_e menuChoice);
static void LcdShowMenu(MenuType_e menuType, MenuChoice_e menuChoice);

static void LcdMenuMove(MenuType_e menuType, MenuMove_e menuMove);

static uint8 MenuMotorOperate();
static uint8 MenuSteerOperate();
static uint8 MenuSpeedOperate();
static uint8 MenuResetOperate();
static void MenuMainOperate();

static void SettingMenuQuit();

/************************************************************************/
/* 初始化                                                               */
/************************************************************************/
void SettingMenuInit()
{
	//LCD_init();//已经初始化过了
	tpm_pwm_duty(TpmSteer, TpmSteerCh, 1500);//舵机归中
	LcdShowMenu(MenuMain, (MenuChoice_e)0);//选中第一个
	MenuMainOperate();
}

/************************************************************************/
/* 显示                                                                 */
/************************************************************************/

static void LcdShowMainMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice >= 0 && menuChoice < MenuMainItemNum);//断言

	if (menuChoice == 0)//第一位
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MainMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MainMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MainMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuMainItemNum - 1)//最后一位
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MainMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MainMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MainMenuItems[menuChoice]);
	}
	else//中间项
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MainMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MainMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MainMenuItems[menuChoice + 1]);
	}
}

static void LcdShowMotorMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice < MenuMotorItemNum);//断言

	if (menuChoice == 0)//第一位
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MotorMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MotorMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MotorMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuMotorItemNum - 1)//最后一位
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MotorMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MotorMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MotorMenuItems[menuChoice]);
	}
	else//中间项
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MotorMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MotorMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MotorMenuItems[menuChoice + 1]);
	}
}

static void LcdShowSteerMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice < MenuSteerItemNum);//断言

	if (menuChoice == 0)//第一位
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SteerMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SteerMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SteerMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuSteerItemNum - 1)//最后一位
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SteerMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SteerMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SteerMenuItems[menuChoice]);
	}
	else//中间项
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SteerMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SteerMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SteerMenuItems[menuChoice + 1]);
	}
}

static void LcdShowSpeedMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice < MenuSpeedItemNum);//断言

	if (menuChoice == 0)//第一位
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SpeedMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SpeedMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SpeedMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuSpeedItemNum - 1)//最后一位
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SpeedMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SpeedMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SpeedMenuItems[menuChoice]);
	}
	else//中间项
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SpeedMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SpeedMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SpeedMenuItems[menuChoice + 1]);
	}
}

static void LcdShowResetMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice < MenuResetItemNum);//断言

	if (menuChoice == 0)//第一位
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)ResetMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)ResetMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)ResetMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuResetItemNum - 1)//最后一位
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)ResetMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)ResetMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)ResetMenuItems[menuChoice]);
	}
	else//中间项
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)ResetMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)ResetMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)ResetMenuItems[menuChoice + 1]);
	}
}

static void LcdShowMenu(MenuType_e menuType, MenuChoice_e menuChoice)//显示菜单（菜单类型，选中菜单）
{
	LcdCls();//清屏
	//这里需要字模
	LCDPrint(0, LcdLine1, MenuTitle);//Title

	switch (menuType)
	{
	case MenuMain://主菜单
		LcdShowMainMenu(menuChoice);
		break;

	case MenuMotor://电机
		LcdShowMotorMenu(menuChoice);
		break;

	case MenuSteer://舵机
		LcdShowSteerMenu(menuChoice);
		break;

	case MenuSpeed://速度
		LcdShowSpeedMenu(menuChoice);
		break;

	case MenuReset://重置
		LcdShowResetMenu(menuChoice);
		break;

	default:
		ASSERT(TRUE);//天空啊，大地啊，海洋啊，程序停下吧！！
		break;
	}


}


/************************************************************************/
/* 菜单控制                                                             */
/************************************************************************/

static void LcdMenuMove(MenuType_e menuType, MenuMove_e menuMove)
{
	int8 menuMoveTemp;//临时变量，用于计算菜单位置
	switch (menuMove)
	{
	case MoveUp:
		menuMoveTemp = -1;
		break;
	case MoveDown:
		menuMoveTemp = 1;
		break;
	default:
		ASSERT(TRUE);
		break;
	}

	switch (menuType)
	{
	case MenuMain:
		menuMoveTemp += MenuChoice.MainMenu;
		if (menuMoveTemp >= 0 && menuMoveTemp < MenuMainItemNum)
		{
			MenuChoice.MainMenu = (MenuChoice_e)menuMoveTemp;
		}
		//LcdShowMainMenu(MenuChoice.MainMenu);
		LcdShowMenu(MenuMain, MenuChoice.MainMenu);
		break;

	case MenuMotor:
		menuMoveTemp += MenuChoice.MotorMenu;
		if (menuMoveTemp >= 0 && menuMoveTemp < MenuMotorItemNum)
		{
			MenuChoice.MotorMenu = (MenuChoice_e)menuMoveTemp;
		}
		LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
		break;

	case MenuSteer:
		menuMoveTemp += MenuChoice.SteerMenu;
		if (menuMoveTemp >= 0 && menuMoveTemp < MenuSteerItemNum)
		{
			MenuChoice.SteerMenu = (MenuChoice_e)menuMoveTemp;
		}
		LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
		break;

	case MenuSpeed:
		menuMoveTemp += MenuChoice.SpeedMenu;
		if (menuMoveTemp >= 0 && menuMoveTemp < MenuSpeedItemNum)
		{
			MenuChoice.SpeedMenu = (MenuChoice_e)menuMoveTemp;
		}
		LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
		break;

	case MenuReset:
		menuMoveTemp += MenuChoice.ResetMenu;
		if (menuMoveTemp >= 0 && menuMoveTemp < MenuResetItemNum)
		{
			MenuChoice.ResetMenu = (MenuChoice_e)menuMoveTemp;
		}
		LcdShowMenu(MenuReset, MenuChoice.ResetMenu);
		break;

	default:
		ASSERT(TRUE);
		break;
	}
}

static uint8 LcdChangeUint16(uint16* num, uint16 max, uint16 min,
	unsigned char * title)
{
	uint16 tempNum = *num;

	LCDPrint(LcdLocal1, LcdLine1, title);
	LCDPrint(LcdLocal2, LcdLine2, (unsigned char *)"max:");
	NumShow(max, LcdLocal3, LcdLine2);
	LCDPrint(LcdLocal2, LcdLine3, (unsigned char *)"min:");
	NumShow(max, LcdLocal3, LcdLine3);
	LCDPrint(LcdLocal2, LcdLine4, (unsigned char *)"set:");
	NumShow(tempNum, LcdLocal3, LcdLine4);

	while (TRUE)//如果按键没有按下，继续执行
	{
		switch (KeyScan())
		{
			//退出
		case FLKeyIrq://退出中断
			return TRUE;
			break;

		case FLKeyEnter:
			*num = tempNum;
			return FALSE;
			break;

		case FLKeyBack://返回
			return FALSE;
			break;

		case FLKeyAdd1:
			tempNum = RANGE(tempNum + 1, max, min);
			NumShow(tempNum, LcdLocal3, LcdLine4);
			break;

		case FLKeySubtract1:
			tempNum = RANGE(tempNum - 1, max, min);
			NumShow(tempNum, LcdLocal3, LcdLine4);
			break;

		case  FLKeyAdd10:
			tempNum = RANGE(tempNum + 10, max, min);
			NumShow(tempNum, LcdLocal3, LcdLine4);
			break;

		case FLKeySubtract10:
			tempNum = RANGE(tempNum - 10, max, min);
			NumShow(tempNum, LcdLocal3, LcdLine4);
			break;

		default:
			break;

		}
	}
}
/************************************************************************/
/* 菜单内容                                                             */
/************************************************************************/

static uint8 MenuMotorOperate()
{
	/*LcdShowMotorMenu((MenuChoice_e)0);*/
	while (TRUE)//如果按键没有按下，继续执行
	{
		switch (KeyScan())
		{
			//退出
		case FLKeyIrq://退出中断
			return TRUE;
			break;

		case FLKeyBack://返回主页
			LcdShowMenu(MenuMain, MenuChoice.MainMenu);
			return FALSE;
			break;


			//上下
		case FlKeyUp:
			LcdMenuMove(MenuMotor, MoveUp);
			break;
		case FlKeyDown:
			LcdMenuMove(MenuMotor, MoveDown);
			break;


			//快捷键
		case FLKeyMotor:
			MenuChoice.MotorMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
			return MenuMotorOperate();
			break;

		case FLKeySteer:
			MenuChoice.SteerMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
			return MenuSteerOperate();
			break;

		case FLKeySpeed:
			MenuChoice.SpeedMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
			return MenuSpeedOperate();
			break;

		case FLKeyReset:
			MenuChoice.ResetMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuReset, MenuChoice.ResetMenu);
			return MenuResetOperate();
			break;

			//////////////////////////////////////////////////////////////////////////
			//超快捷
		case FLKeyKp:
			MenuChoice.MotorMenu = MenuMotorKp;
			LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
			break;

		case FLKeyKi:
			MenuChoice.MotorMenu = MenuMotorKi;
			LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
			break;

		case FLKeyKd:
			MenuChoice.MotorMenu = MenuMotorKd;
			LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
			break;

		case FLKeyNormalizing:
			AdcNormalizingInit();
			LcdShowMenu(MenuMain, MenuChoice.MainMenu);//返回菜单
			break;

		default:
			LcdErrShow(LcdErrKeyWrong);
			break;
		}
	}
	//return FALSE;//unreachable
}

static uint8 MenuSteerOperate()
{
	while (TRUE)//如果按键没有按下，继续执行
	{
		switch (KeyScan())
		{
			//退出
		case FLKeyIrq://退出中断
			return TRUE;
			break;

		case FLKeyBack://返回主页
			LcdShowMenu(MenuMain, MenuChoice.MainMenu);
			return FALSE;
			break;

		case FLKeyEnter:
			switch (MenuChoice.SteerMenu)
			{
			case MenuSteerAdcDomain:
				SteerFuzzyDomainScan();
				LcdShowMenu(MenuMain, MenuChoice.MainMenu);
				break;

			case MenuSteerSteerDomain:
				LcdChangeUint16(&FreecaleConfig.Config.Steer.SteerDomainDif, 200, 0,
					(unsigned char *)"Steer Domain");
				break;

			default:
				break;
			}
			break;

			//上下
		case FlKeyUp:
			LcdMenuMove(MenuSteer, MoveUp);
			break;
		case FlKeyDown:
			LcdMenuMove(MenuSteer, MoveDown);
			break;

			//快捷键
		case FLKeyMotor:
			MenuChoice.MotorMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
			return MenuMotorOperate();
			break;

		case FLKeySteer:
			MenuChoice.SteerMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
			return MenuSteerOperate();
			break;

		case FLKeySpeed:
			MenuChoice.SpeedMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
			return MenuSpeedOperate();
			break;

		case FLKeyReset:
			MenuChoice.ResetMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuReset, MenuChoice.ResetMenu);
			return MenuResetOperate();
			break;

		default:
			LcdErrShow(LcdErrKeyWrong);
			break;
		}
	}
	//return FALSE;//unreachable
}

static uint8 MenuSpeedOperate()
{
	while (TRUE)//如果按键没有按下，继续执行
	{
		switch (KeyScan())
		{
			//退出
		case FLKeyIrq://退出中断
			return TRUE;
			break;

		case FLKeyBack://返回主页
			LcdShowMenu(MenuMain, MenuChoice.MainMenu);
			return FALSE;
			break;


			//上下
		case FlKeyUp:
			LcdMenuMove(MenuSpeed, MoveUp);
			break;
		case FlKeyDown:
			LcdMenuMove(MenuSpeed, MoveDown);
			break;



			//快捷键
		case FLKeyMotor:
			MenuChoice.MotorMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
			return MenuMotorOperate();
			break;

		case FLKeySteer:
			MenuChoice.SteerMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
			return MenuSteerOperate();
			break;

		case FLKeySpeed:
			MenuChoice.SpeedMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
			return MenuSpeedOperate();
			break;

		case FLKeyReset:
			MenuChoice.ResetMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuReset, MenuChoice.ResetMenu);
			return MenuResetOperate();
			break;


		default:
			LcdErrShow(LcdErrKeyWrong);
			break;
		}
	}
	//return FALSE;//unreachable
}

static uint8 MenuResetOperate()
{
	while (TRUE)//如果按键没有按下，继续执行
	{
		switch (KeyScan())
		{
			//退出
		case FLKeyIrq://退出中断
			return TRUE;
			break;

		case FLKeyBack://返回主页
			//LcdShowMainMenu(MenuChoice.MainMenu);
			LcdShowMenu(MenuMain, MenuChoice.MainMenu);
			return FALSE;
			break;


			//上下
		case FlKeyUp:
			LcdMenuMove(MenuReset, MoveUp);
			break;
		case FlKeyDown:
			LcdMenuMove(MenuReset, MoveDown);
			break;

		case FLKeyEnter:
			switch ((MenuChoice_e)MenuChoice.ResetMenu)
			{
			case MenuResetCancel1:
			case MenuResetCancel2:
				LcdShowMenu(MenuMain, MenuChoice.MainMenu);
				return FALSE;
				break;

			case MenuResetAccept:
				LCDPrintInverse(LcdTitleLocal, LcdTitleLine, (unsigned char *)"RUNNING...     ");
				if (ConfigSetDefaultInEeprom() != ConfigAllGreen)
				{
					LcdErrShow(SettingErrFail);
				}
				else
				{
					LCDPrintInverse(LcdTitleLocal, LcdTitleLine, (unsigned char *)"DONE.      ");
				}
				break;

			default:
				ASSERT(TRUE);
				break;
			}
			//快捷键
		case FLKeyMotor:
			MenuChoice.MotorMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
			return MenuMotorOperate();
			break;

		case FLKeySteer:
			MenuChoice.SteerMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
			return MenuSteerOperate();
			break;

		case FLKeySpeed:
			MenuChoice.SpeedMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
			return MenuSpeedOperate();
			break;

		case FLKeyReset:
			MenuChoice.ResetMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuReset, MenuChoice.ResetMenu);
			return MenuResetOperate();
			break;
			//////////////////////////////////////////////////////////////////////////

		default:
			LcdErrShow(LcdErrKeyWrong);
			break;
		}
	}
	//return FALSE;//unreachable
}

static void MenuMainOperate()
{
	uint8 exitFunc = FALSE;
	MenuChoice.MainMenu = (MenuChoice_e)0;
	while (TRUE)//如果按键没有按下，继续执行
	{
		if (exitFunc)
		{
			SettingMenuQuit();
			break;
		}
		switch (KeyScan())
		{
		case FlKeyUp:
			LcdMenuMove(MenuMain, MoveUp);
			break;
		case FlKeyDown:
			LcdMenuMove(MenuMain, MoveDown);
			break;

			//进入
		case FLKeyEnter:
			switch ((MenuChoice_e)MenuChoice.MainMenu)
			{
			case MenuMainMotor:
				MenuChoice.MotorMenu = (MenuChoice_e)0;
				LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
				exitFunc = MenuMotorOperate();//这么写，便于判断是否退出整个按键中断
				break;

			case MenuMainSteer:
				MenuChoice.SteerMenu = (MenuChoice_e)0;
				LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
				exitFunc = MenuSteerOperate();
				break;

			case MenuMainSpeed:
				MenuChoice.SpeedMenu = (MenuChoice_e)0;
				LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
				exitFunc = MenuSpeedOperate();
				break;

			case MenuMainReset:
				MenuChoice.ResetMenu = (MenuChoice_e)0;
				LcdShowMenu(MenuReset, MenuChoice.ResetMenu);
				exitFunc = MenuResetOperate();
				break;

			case MenuMainAdcNor:
				AdcNormalizingInit();
				LcdShowMenu(MenuMain, MenuChoice.MainMenu);
				break;


			default:
				ASSERT(TRUE);
				break;
			}
			break;


			//快捷
		case FLKeyMotor:
			MenuChoice.MotorMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
			exitFunc = MenuMotorOperate();
			break;

		case FLKeySteer:
			MenuChoice.SteerMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
			exitFunc = MenuSteerOperate();
			break;

		case FLKeySpeed:
			MenuChoice.SpeedMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
			exitFunc = MenuSpeedOperate();
			break;

		case FLKeyReset:
			MenuChoice.ResetMenu = (MenuChoice_e)0;
			LcdShowMenu(MenuReset, MenuChoice.ResetMenu);
			exitFunc = MenuResetOperate();
			break;
			//////////////////////////////////////////////////////////////////////////

			//超快捷
		case FLKeyKp:
			switch (MenuChoice.MainMenu)
			{
			case MenuMainMotor:
				MenuChoice.MotorMenu = MenuMotorKp;
				LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
				exitFunc = MenuMotorOperate();
				break;

			default:
				LcdErrShow(LcdErrKeyWrong);
				break;
			}
			break;

		case FLKeyKi:
			switch (MenuChoice.MainMenu)
			{
			case MenuMainMotor:
				MenuChoice.MotorMenu = MenuMotorKi;
				LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
				exitFunc = MenuMotorOperate();
				break;

			default:
				LcdErrShow(LcdErrKeyWrong);
				break;
			}
			break;

		case FLKeyKd:
			switch (MenuChoice.MainMenu)
			{
			case MenuMainMotor:
				MenuChoice.MotorMenu = MenuMotorKd;
				LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
				exitFunc = MenuMotorOperate();
				break;
                                

			default:
				LcdErrShow(LcdErrKeyWrong);
				break;
			}
			break;
			

			//////////////////////////////////////////////////////////////////////////
		case FLKeyIrq:
			exitFunc = TRUE;
			break;

		default:
			LcdErrShow(LcdErrKeyWrong);
			break;
		}
	}
}

/************************************************************************/
/* 退出                                                                 */
/************************************************************************/
static void SettingMenuQuit()
{
	LcdCls();//清屏
	//LcdShowAllData();//屏幕
	//while (FLKeyCheck(FLKeyIrq) == KEY_DOWN);//这句话加到flkeycheck里了
	EnableInterrupts();
	DELAY();//按键消抖
	FLKeyIrqEnable();
}
