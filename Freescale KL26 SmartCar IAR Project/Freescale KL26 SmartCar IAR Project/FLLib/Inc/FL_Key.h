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

	FLKeyPortNum,
};

typedef enum
{
	//#warning please change these code !(very important)
	FlKeyUp = 2,//上
	FlKeyDown = 6,//下

	FLKeyAdd1 = 2,//+1
	FLKeySubtract1 = 6,//-1
	FLKeyAdd10 = 3,//+10
	FLKeySubtract10 = 7,//-10

	FLKeyReserve1 = 12,//保留

	FLKeyNormalizing = 13,//归一化

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
	FLKeyMenu = 15,//进入、退出菜单

	FLKeyAdcNorExit = 0,//开跑了
	FLKeyReNormalizing = 1,//重新归一化
	FLKeySwitch = 2,//切换显示最大值或最小值

	FLNoKeyDown = 16,//没有按键按下
	FLKeyMax = 16,//按键总数
} FL_KEY_e;//这里面数值需要调整一下

#define IrqKeyPort PortC//定义中断按钮端口号，可选PortC或PortD
#if Key_f == 0
#define IrqKeyPortNum 7//定义中断引脚号
#else
#define IrqKeyPortNum 0//定义中断引脚号
#endif

//extern struct MenuChoice_s MenuChoice;


InitRepot_e FLKeyInit();
KEY_STATUS_e    FLKeyGet(FL_KEY_e key);             //检测key状态（不带延时消抖）
KEY_STATUS_e    FLKeyCheck(FL_KEY_e key);           //检测key状态（带延时消抖）
void FLKeyIrqEnable();
void FLKeyIrqDisable();
void FLIrqHandle();
void FLIrqKeyDown();
FL_KEY_e KeyScan();//扫描所有按键
FL_KEY_e KeyScanWithoutIrq();//不扫描按键第四行



#endif//_FL_KEY_