
#include "FL_SettingMenu.h"
#include "FL_OLCD.h"
#include "fl_config.h"




const unsigned char * MainMenuItems[MenuMainItemNum] =
{
	"Perfet",
	"CarThis",
	"StartDelay",
	"Motor",
	"Steer",
	"Speed",
	"mode",
	"Normalizing",
	"Reset EepRom",
};

const unsigned char * MotorMenuItems[MenuMotorItemNum] =
{
	"Motor Kp",
	"Motor Ki",
	"Motor Kd",
};

const unsigned char * SteerMenuItems[MenuSteerItemNum] =
{
	"Steer Kp",
	"Steer Ki",
	"Steer Kd",
	"Adc Domain",
	"Steer Domain",
	"Steer Method"
};

const unsigned char * SpeedMenuItems[MenuSpeedItemNum] =
{
	"LineSpeed",
	"TurnSpeed",
	"LostLineSpeed",
	"LostAdcMin",
	"LostAdcVerMin",
};

const unsigned char * ResetMenuItems[MenuResetItemNum] =
{
	"Cancel",
	"Cancel",
	"Accept",
};

const unsigned char * ModeMenuItems[MenuModeItemNum] =
{
	"NrfStartCar",
	"Ultrasonic",
	"EndLine",
	"PowerOnDelay",
	"MpuctrlSpeed",
	"DistCtrlSpeed",
	"Nrf24l01 enable",
	"NrfSendDistance",
	"NrfSendAdc",
	"MotorLowValid"
};


struct MenuChoice_s MenuChoice = { 
	(MenuChoice_e)0,
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

static void LcdShowModeMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice < MenuModeItemNum);//断言

	if (menuChoice == 0)//第一位
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)ModeMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)ModeMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)ModeMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuModeItemNum - 1)//最后一位
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)ModeMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)ModeMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)ModeMenuItems[menuChoice]);
	}
	else//中间项
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)ModeMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)ModeMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)ModeMenuItems[menuChoice + 1]);
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

	case MenuMode:
		LcdShowModeMenu(menuChoice);
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

	case MenuMode:
		menuMoveTemp += MenuChoice.ModeMenu;
		if (menuMoveTemp >= 0 && menuMoveTemp < MenuModeItemNum)
		{
			MenuChoice.ModeMenu = (MenuChoice_e)menuMoveTemp;
		}
		LcdShowMenu(MenuMode, MenuChoice.ModeMenu);
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

	LcdCls();
	LCDPrint(LcdLocal1, LcdLine1, title);
	LCDPrint(LcdLocal2, LcdLine2, (unsigned char *)"max:");
	NumShow4(max, LcdLocal3, LcdLine2);
	LCDPrint(LcdLocal2, LcdLine3, (unsigned char *)"min:");
	NumShow4(min, LcdLocal3, LcdLine3);
	LCDPrint(LcdLocal2, LcdLine4, (unsigned char *)"set:");
	NumShow4(tempNum, LcdLocal3, LcdLine4);

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
			return 0xff;
			break;

		case FLKeyBack://返回
			return FALSE;
			break;

		case FLKeyAdd1:
			tempNum = RANGE(tempNum + 1, max, min);
			NumShow4(tempNum, LcdLocal3, LcdLine4);
			break;

		case FLKeySubtract1:
			tempNum = RANGE(tempNum - 1, max, min);
			NumShow4(tempNum, LcdLocal3, LcdLine4);
			break;

		case  FLKeyAdd10:
			tempNum = RANGE(tempNum + 10, max, min);
			NumShow4(tempNum, LcdLocal3, LcdLine4);
			break;

		case FLKeySubtract10:
			tempNum = RANGE(tempNum - 10, max, min);
			NumShow4(tempNum, LcdLocal3, LcdLine4);
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

		case FLKeyEnter:
			switch (MenuChoice.MotorMenu)
			{
			case MenuMotorKp:
				LcdChangeUint16(&FreecaleConfig.Config.Motor.Pid.Pid.P, PidPrecision * 10, 0,
					(unsigned char *)"Motor Kp");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
				break;

			case MenuMotorKi:
				LcdChangeUint16(&FreecaleConfig.Config.Motor.Pid.Pid.I, PidPrecision * 10, 0,
					(unsigned char *)"Motor Ki");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
				break;

			case MenuMotorKd:
				LcdChangeUint16(&FreecaleConfig.Config.Motor.Pid.Pid.D, PidPrecision * 10, 0,
					(unsigned char *)"Motor Kd");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
				break;

			default:
				break;
			}
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
			case MenuSteerKp:
				LcdChangeUint16(&FreecaleConfig.Config.Steer.Pid.Pid.P, PidPrecision * 10, 0,
					(unsigned char *)"Steer Kp");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
				break;

			case  MenuSteerKi:
				LcdChangeUint16(&FreecaleConfig.Config.Steer.Pid.Pid.I, PidPrecision * 10, 0,
					(unsigned char *)"Steer Ki");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
				break;

			case MenuSteerKd:
				LcdChangeUint16(&FreecaleConfig.Config.Steer.Pid.Pid.D, PidPrecision * 10, 0,
					(unsigned char *)"Steer Kd");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
				break;

			case MenuSteerAdcDomain:
				SteerFuzzyDomainScan();
				LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
				break;

			case MenuSteerSteerDomain:
				LcdChangeUint16(&FreecaleConfig.Config.Steer.SteerDomainDif, 200, 0,
					(unsigned char *)"Steer Domain");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
				LCDPrintInverse(LcdTitleLocal, LcdTitleLine, (unsigned char *)"Test...     ");
				tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + 3 * FreecaleConfig.Config.Steer.SteerDomainDif);
				DELAY_MS(1000);
				LCDPrintInverse(LcdTitleLocal, LcdTitleLine, (unsigned char *)"Done        ");
				tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty);
				break;

			case MenuSteerMethod:
				uint16 temp = FreecaleConfig.Config.Steer.SteerCtrlMethod;
				LcdChangeUint16(&temp, SteerCtrlMethod_Max - 1, 0, "steer method");
				FreecaleConfig.Config.Steer.SteerCtrlMethod = (uint8)temp;
				LcdShowMenu(MenuSteer, MenuChoice.SteerMenu);
				ConfigWrite(&FreecaleConfig);
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

		case FLKeyEnter:
			switch (MenuChoice.SpeedMenu)
			{
			case MenuSpeedLine:
				LcdChangeUint16(&FreecaleConfig.Config.Motor.Speed.LineSpeed, 9999, 0,
					(unsigned char *)"Speed Line");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
				break;

			case MenuSpeedTurn:
				LcdChangeUint16(&FreecaleConfig.Config.Motor.Speed.TurnSpeed, 9999, 0,
					(unsigned char *)"Speed Turn");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
				break;

			case MenuSpeedLost:
				LcdChangeUint16(&FreecaleConfig.Config.Motor.Speed.LostLineSpeed, 9999, 0,
					(unsigned char *)"Speed Lost");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
				break;

			case MenuSpeedLostAdcMin:
				LcdChangeUint16(&FreecaleConfig.Config.LostAdcMin, 1000, 0,
					(unsigned char *)"LostAdcMin");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
				break;

			case MenuSpeedLostAdcVerticalMin:
				LcdChangeUint16(&FreecaleConfig.Config.LostAdcVerticalMin, 1000, 0,
					(unsigned char *)"LostAdcVerticalMin");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuSpeed, MenuChoice.SpeedMenu);
				break;

			default:
				break;
			}
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
					LcdCls();
					LCDPrintInverse(LcdTitleLocal, LcdTitleLine, (unsigned char *)"DONE.");
					LCDPrint(LcdLocal1, LcdLine3, (unsigned char *)"Please Reboot!");
					while (1);
				}
				break;

			default:
				ASSERT(TRUE);
				break;
			}
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

		default:
			LcdErrShow(LcdErrKeyWrong);
			break;
		}
	}
	//return FALSE;//unreachable
}

static uint8 MenuModeOperate()
{
	SwitchMode * modeSwitch = (SwitchMode *)&FreecaleConfig.Config.Mode;
	LCDPrintInverse(LcdLocal1, LcdLine1,
		(*(modeSwitch + (uint8)MenuChoice.ModeMenu) == On) ?
		(unsigned char *) "On " :
		(unsigned char *) "Off");
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

		case FLKeyEnter:
			*(modeSwitch + (uint8)MenuChoice.ModeMenu) =
				~*(modeSwitch + (uint8)MenuChoice.ModeMenu) &0x01;
			LCDPrintInverse(LcdLocal1, LcdLine1,
				(*(modeSwitch + (uint8)MenuChoice.ModeMenu) == On) ?
				(unsigned char *) "On " :
				(unsigned char *) "Off");
			ConfigWrite(&FreecaleConfig);

			switch (MenuChoice.ModeMenu)
			{
			case MenuModeMotorLowValid:
				tpm_pwm_duty(TpmMotor, TpmMotorCh0, 0);
				break;

			default:
				break;
			}
			break;

			//上下
		case FlKeyUp:
			LcdMenuMove(MenuMode, MoveUp);
			LCDPrintInverse(LcdLocal1, LcdLine1,
				(*(modeSwitch + (uint8)MenuChoice.ModeMenu) == On) ?
				(unsigned char *) "On " :
				(unsigned char *) "Off");
			break;

		case FlKeyDown:
			LcdMenuMove(MenuMode, MoveDown);
			LCDPrintInverse(LcdLocal1, LcdLine1,
				(*(modeSwitch + (uint8)MenuChoice.ModeMenu) == On) ?
				(unsigned char *) "On " :
				(unsigned char *) "Off");
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
			case MenuMainPerfet:
#include "fl_Perfet_Plan.h"
				if (LcdChangeUint16(&PerfetPlan, PlanNum - 1, 0,
					(unsigned char *)"Perfet Plan") == 0xff)
				{
					CarToPerfet();
				}
				LcdShowMenu(MenuMain, MenuChoice.MainMenu);
				break;

			case MenuMainCarThis:
				uint16 carThisTemp = 0;
				LcdChangeUint16(&carThisTemp, CarNum - 1, 0,
					(unsigned char *)"CarThis");
				FreecaleConfig.Config.CarThis = (uint8)carThisTemp;
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuMain, MenuChoice.MainMenu);
				break;

			case MenuMainStartDelay:
				LcdChangeUint16(&FreecaleConfig.Config.CarDelay, 9999, 0,
					(unsigned char *)"Start Delay");
				ConfigWrite(&FreecaleConfig);
				LcdShowMenu(MenuMain, MenuChoice.MainMenu);
				break;

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

			case MenuMainMode:
				MenuChoice.ModeMenu = (MenuChoice_e)0;
				LcdShowMenu(MenuMode, MenuChoice.ModeMenu);
				exitFunc = MenuModeOperate();
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
	//ConfigWrite(&FreecaleConfig);
	EnableInterrupts();
	DELAY();//按键消抖
	FLKeyIrqEnable();
}
