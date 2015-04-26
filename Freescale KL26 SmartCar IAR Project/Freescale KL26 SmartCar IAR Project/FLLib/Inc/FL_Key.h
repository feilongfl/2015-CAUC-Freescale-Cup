#include "VCAN_key.h"

#ifndef _FL_KEY_
#define _FL_KEY_

#define KeyLineNum 4
#define KeyRankNum 4
#define KeyMax		(KeyLineNum * KeyRankNum)
#define KeyPortMax  (KeyLineNum + KeyRankNum)

enum//��������
{
	FLKeyLine,//��
	FLKeyRank,//��

	FLKeyPortNum,
};

typedef enum
{
	//#warning please change these code !(very important)
	FlKeyUp = 2,//��
	FlKeyDown = 6,//��

	FLKeyAdd1 = 2,//+1
	FLKeySubtract1 = 6,//-1
	FLKeyAdd10 = 3,//+10
	FLKeySubtract10 = 7,//-10

	FLKeyReserve1 = 12,//����

	FLKeyNormalizing = 13,//��һ��

	FLKeyKp = 0,//Kp
	FLKeyKi = 4,//Ki
	FLKeyKd = 8,//Kd

	FLKeySpeed = 9,//����
	FLKeyMotor = 1,//���
	FLKeySteer = 5,//���

	FLKeyEnter = 11,//enter
	FLKeyBack = 10,//����

	FLKeyReset = 14,//�ָ�Ĭ���趨

	FLKeyIrq = 15,//���롢�˳������ж�
	FLKeyMenu = 15,//���롢�˳��˵�

	FLKeyAdcNorExit = 0,//������
	FLKeyReNormalizing = 1,//���¹�һ��
	FLKeySwitch = 2,//�л���ʾ���ֵ����Сֵ

	FLNoKeyDown = 16,//û�а�������
	FLKeyMax = 16,//��������
} FL_KEY_e;//��������ֵ��Ҫ����һ��

#define IrqKeyPort PortC//�����жϰ�ť�˿ںţ���ѡPortC��PortD
#if Key_f == 0
#define IrqKeyPortNum 7//�����ж����ź�
#else
#define IrqKeyPortNum 0//�����ж����ź�
#endif

//extern struct MenuChoice_s MenuChoice;


InitRepot_e FLKeyInit();
KEY_STATUS_e    FLKeyGet(FL_KEY_e key);             //���key״̬��������ʱ������
KEY_STATUS_e    FLKeyCheck(FL_KEY_e key);           //���key״̬������ʱ������
void FLKeyIrqEnable();
void FLKeyIrqDisable();
void FLIrqHandle();
void FLIrqKeyDown();
FL_KEY_e KeyScan();//ɨ�����а���
FL_KEY_e KeyScanWithoutIrq();//��ɨ�谴��������



#endif//_FL_KEY_