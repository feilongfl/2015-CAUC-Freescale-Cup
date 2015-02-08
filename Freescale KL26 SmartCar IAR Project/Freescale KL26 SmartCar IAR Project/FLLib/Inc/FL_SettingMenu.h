#include "common.h"
#include "fl_Olcd.h"
#include "FL_Key.h"
#include "fl_pid.h"

#ifndef _FL_SETTINGMENU_
#define _FL_SETTINGMENU_



//////////////////////////////////////////////////////////////////////////

#warning pid��ʼֵδ�趨
//״ֵ̬
extern volatile struct Pid_s PidMotor;//���
extern volatile struct Pid_s PidSteer;//���
extern const struct Pid_s volatile *PidMotorAddress;//�����ַ
extern const struct Pid_s volatile *PidSteerAddress;//�����ַ

extern volatile struct Speed_s Speed;

#warning pid���ֵδ�趨
extern const struct Pid_s PidMotorMax;//���
extern const struct Pid_s PidSteerMax;//���
extern const struct Pid_s *PidMotorMaxAddress;//�����ַ
extern const struct Pid_s *PidSteerMaxAddress;//�����ַ
 //��Сֵ
#warning pid��Сֵδ�趨
extern const struct Pid_s PidMotorMin;//���
extern const struct Pid_s PidSteerMin;//���
extern const struct Pid_s *PidMotorMinAddress;//�����ַ
extern const struct Pid_s *PidSteerMinAddress;//�����ַ

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
/* ����                                                                 */
/************************************************************************/
void MotorPidChange(Pid_e pidType, int8 chaangeNum);//�޸ĵ��pid����
void SteerPidChange(Pid_e pidType, int8 chaangeNum);//�޸Ķ��pid����
void SpeedSet(int8 changeNum);//���ת��

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


typedef enum
{
	OverMax,//�������ֵ
	OverMin,//������Сֵ

	KeyWrong,//��ǰ���治֧�ָð���

	Other,//δ�������

	LcdErrNumbers,//��������
}LcdErr_e;//�����

#define LcdErrMsgLength 9//������ʾ���ֳ���


/************************************************************************/
/* �˵�����                                                             */
/************************************************************************/
void LcdMenuMove(MenuType_e menuType, MenuMove_e menuMove);
/************************************************************************/
/* ��ʼ��                                                               */
/************************************************************************/
void SettingMenuInit();

/************************************************************************/
/* ��ʾ                                                                 */
/************************************************************************/
void LcdShowMenu(MenuType_e menuType, MenuChoice_e menuChoice);//��ʾ���˵�
void LcdShowMenu(MenuType_e menuType, MenuChoice_e menuChoice);//��ʾ�˵����˵����ͣ�ѡ�в˵���
void LcdShowMotorMenu(MenuChoice_e menuChoice);//��ʾ������ò˵�
void LcdErrShow(LcdErr_e lcdErr);

void MenuMainOperate();
#endif//_FL_SETTINGMENU_
