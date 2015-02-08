#include "VCAN_key.h"

#ifndef _FL_KEY_
#define _FL_KEY_

#define KeyLineNum 4
#define KeyRankNum 4
#define KeyMax		(KeyLineNum * KeyRankNum)
#define KeyPortMax  (KeyLineNum + KeyRankNum)

enum//按键行列
{
	FLKeyLine,//行
	FLKeyRank,//列

	FLKeyRange,
};

typedef enum
{
	#warning please change these code !(very important)
	FlKeyUp = 2,//上
	FlKeyDown = 6,//下

	FLKeyAdd1 = 2,//+1
	FLKeySubtract1 = 6,//-1
	FLKeyAdd10 = 3,//+10
	FLKeySubtract10 = 7,//-10

	FLKeyReserve1 = 12,//保留
	FLKeyReserve2 = 13,

	FLKeyKp = 0,//Kp
	FLKeyKi = 4,//Ki
	FLKeyKd = 8,//Kd

	FLKeySpeed = 9,//车速
	FLKeyMotor = 1,//电机
	FLKeySteer = 5,//舵机

	FLKeyEnter = 11,//enter
	FLKeyBack = 10,//返回

	FLKeyReset = 14,//恢复默认设定

	FLKeyIrq = 15,//进入、退出按键中断

	FLKeyMax = 16,//按键总数
} FL_KEY_e;//这里面数值需要调整一下

#define IrqKeyPort PortC//定义中断按钮端口号，可选PortC或PortD
#define IrqKeyPortNum 7//定义中断引脚号


extern struct MenuChoice_s MenuChoice;


void FLKeyInit();
KEY_STATUS_e    FLKeyGet(FL_KEY_e key);             //检测key状态（不带延时消抖）
KEY_STATUS_e    FLKeyCheck(FL_KEY_e key);           //检测key状态（带延时消抖）
void FLKeyIrqEnable();
void FLKeyIrqDisable();
void FLIrqHandle();
void FLIrqKeyDown();
FL_KEY_e KeyScan();




#endif//_FL_KEY_