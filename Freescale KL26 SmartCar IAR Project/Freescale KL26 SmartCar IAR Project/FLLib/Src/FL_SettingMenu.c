
#include "FL_SettingMenu.h"
#include "FL_OLCD.h"
#include "fl_config.h"




const unsigned char * MainMenuItems[MenuMainItemNum] =
{
	"�������",
	"�������",
	"��������",
	"��һ��",
	"Reset EepRom",
};

const unsigned char * MotorMenuItems[MenuMotorItemNum] =
{
	"���Kp",
	"���Ki",
	"���Kd",
	"���õ��",
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
	"ȡ��",
	"ȡ��",
	"ȷ������",
};

struct MenuChoice_s MenuChoice = { 
	(MenuChoice_e)0,
	(MenuChoice_e)0,
	(MenuChoice_e)0,
	(MenuChoice_e)0
};
struct MenuChoice_s * MenuChoiceAddress = &MenuChoice;


/************************************************************************/
/* ��̬��������                                                                     */
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
/* ��ʼ��                                                               */
/************************************************************************/
void SettingMenuInit()
{
	//LCD_init();//�Ѿ���ʼ������
	tpm_pwm_duty(TpmSteer, TpmSteerCh, 1500);//�������
	LcdShowMenu(MenuMain, (MenuChoice_e)0);//ѡ�е�һ��
	MenuMainOperate();
}

/************************************************************************/
/* ��ʾ                                                                 */
/************************************************************************/

static void LcdShowMainMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice >= 0 && menuChoice < MenuMainItemNum);//����

	if (menuChoice == 0)//��һλ
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MainMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MainMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MainMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuMainItemNum - 1)//���һλ
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MainMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MainMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MainMenuItems[menuChoice]);
	}
	else//�м���
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MainMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MainMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MainMenuItems[menuChoice + 1]);
	}
}

static void LcdShowMotorMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice < MenuMotorItemNum);//����

	if (menuChoice == 0)//��һλ
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MotorMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MotorMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MotorMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuMotorItemNum - 1)//���һλ
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MotorMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MotorMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MotorMenuItems[menuChoice]);
	}
	else//�м���
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)MotorMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)MotorMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)MotorMenuItems[menuChoice + 1]);
	}
}

static void LcdShowSteerMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice < MenuSteerItemNum);//����

	if (menuChoice == 0)//��һλ
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SteerMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SteerMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SteerMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuSteerItemNum - 1)//���һλ
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SteerMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SteerMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SteerMenuItems[menuChoice]);
	}
	else//�м���
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SteerMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SteerMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SteerMenuItems[menuChoice + 1]);
	}
}

static void LcdShowSpeedMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice < MenuSpeedItemNum);//����

	if (menuChoice == 0)//��һλ
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SpeedMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SpeedMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SpeedMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuSpeedItemNum - 1)//���һλ
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SpeedMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SpeedMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SpeedMenuItems[menuChoice]);
	}
	else//�м���
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)SpeedMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)SpeedMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)SpeedMenuItems[menuChoice + 1]);
	}
}

static void LcdShowResetMenu(MenuChoice_e menuChoice)
{
	ASSERT(menuChoice < MenuResetItemNum);//����

	if (menuChoice == 0)//��һλ
	{
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine1, (unsigned char *)ResetMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)ResetMenuItems[menuChoice + 1]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)ResetMenuItems[menuChoice + 2]);
	}
	else if (menuChoice == MenuResetItemNum - 1)//���һλ
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)ResetMenuItems[menuChoice - 2]);
		LCDPrint(LcdMenuLocal, LcdMenuLine2, (unsigned char *)ResetMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine3, (unsigned char *)ResetMenuItems[menuChoice]);
	}
	else//�м���
	{
		LCDPrint(LcdMenuLocal, LcdMenuLine1, (unsigned char *)ResetMenuItems[menuChoice - 1]);
		LCDPrintInverse(LcdMenuLocal, LcdMenuLine2, (unsigned char *)ResetMenuItems[menuChoice]);
		LCDPrint(LcdMenuLocal, LcdMenuLine3, (unsigned char *)ResetMenuItems[menuChoice + 1]);
	}
}

static void LcdShowMenu(MenuType_e menuType, MenuChoice_e menuChoice)//��ʾ�˵����˵����ͣ�ѡ�в˵���
{
	LcdCls();//����
	//������Ҫ��ģ
	LCDPrint(0, LcdLine1, MenuTitle);//Title

	switch (menuType)
	{
	case MenuMain://���˵�
		LcdShowMainMenu(menuChoice);
		break;

	case MenuMotor://���
		LcdShowMotorMenu(menuChoice);
		break;

	case MenuSteer://���
		LcdShowSteerMenu(menuChoice);
		break;

	case MenuSpeed://�ٶ�
		LcdShowSpeedMenu(menuChoice);
		break;

	case MenuReset://����
		LcdShowResetMenu(menuChoice);
		break;

	default:
		ASSERT(TRUE);//��հ�����ذ������󰡣�����ͣ�°ɣ���
		break;
	}


}


/************************************************************************/
/* �˵�����                                                             */
/************************************************************************/

static void LcdMenuMove(MenuType_e menuType, MenuMove_e menuMove)
{
	int8 menuMoveTemp;//��ʱ���������ڼ���˵�λ��
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

	while (TRUE)//�������û�а��£�����ִ��
	{
		switch (KeyScan())
		{
			//�˳�
		case FLKeyIrq://�˳��ж�
			return TRUE;
			break;

		case FLKeyEnter:
			*num = tempNum;
			return FALSE;
			break;

		case FLKeyBack://����
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
/* �˵�����                                                             */
/************************************************************************/

static uint8 MenuMotorOperate()
{
	/*LcdShowMotorMenu((MenuChoice_e)0);*/
	while (TRUE)//�������û�а��£�����ִ��
	{
		switch (KeyScan())
		{
			//�˳�
		case FLKeyIrq://�˳��ж�
			return TRUE;
			break;

		case FLKeyBack://������ҳ
			LcdShowMenu(MenuMain, MenuChoice.MainMenu);
			return FALSE;
			break;


			//����
		case FlKeyUp:
			LcdMenuMove(MenuMotor, MoveUp);
			break;
		case FlKeyDown:
			LcdMenuMove(MenuMotor, MoveDown);
			break;


			//��ݼ�
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
			//�����
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
			LcdShowMenu(MenuMain, MenuChoice.MainMenu);//���ز˵�
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
	while (TRUE)//�������û�а��£�����ִ��
	{
		switch (KeyScan())
		{
			//�˳�
		case FLKeyIrq://�˳��ж�
			return TRUE;
			break;

		case FLKeyBack://������ҳ
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

			//����
		case FlKeyUp:
			LcdMenuMove(MenuSteer, MoveUp);
			break;
		case FlKeyDown:
			LcdMenuMove(MenuSteer, MoveDown);
			break;

			//��ݼ�
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
	while (TRUE)//�������û�а��£�����ִ��
	{
		switch (KeyScan())
		{
			//�˳�
		case FLKeyIrq://�˳��ж�
			return TRUE;
			break;

		case FLKeyBack://������ҳ
			LcdShowMenu(MenuMain, MenuChoice.MainMenu);
			return FALSE;
			break;


			//����
		case FlKeyUp:
			LcdMenuMove(MenuSpeed, MoveUp);
			break;
		case FlKeyDown:
			LcdMenuMove(MenuSpeed, MoveDown);
			break;



			//��ݼ�
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
	while (TRUE)//�������û�а��£�����ִ��
	{
		switch (KeyScan())
		{
			//�˳�
		case FLKeyIrq://�˳��ж�
			return TRUE;
			break;

		case FLKeyBack://������ҳ
			//LcdShowMainMenu(MenuChoice.MainMenu);
			LcdShowMenu(MenuMain, MenuChoice.MainMenu);
			return FALSE;
			break;


			//����
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
			//��ݼ�
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
	while (TRUE)//�������û�а��£�����ִ��
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

			//����
		case FLKeyEnter:
			switch ((MenuChoice_e)MenuChoice.MainMenu)
			{
			case MenuMainMotor:
				MenuChoice.MotorMenu = (MenuChoice_e)0;
				LcdShowMenu(MenuMotor, MenuChoice.MotorMenu);
				exitFunc = MenuMotorOperate();//��ôд�������ж��Ƿ��˳����������ж�
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


			//���
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

			//�����
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
/* �˳�                                                                 */
/************************************************************************/
static void SettingMenuQuit()
{
	LcdCls();//����
	//LcdShowAllData();//��Ļ
	//while (FLKeyCheck(FLKeyIrq) == KEY_DOWN);//��仰�ӵ�flkeycheck����
	EnableInterrupts();
	DELAY();//��������
	FLKeyIrqEnable();
}
