/************************************************************************/
/*       头文件                                              */
/************************************************************************/
#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_ADC.h"


#ifndef _FL_STEER_
#define _FL_STEER_


/************************************************************************/
/*              宏定义                                               */
/************************************************************************/
//舵机常规属性
#define SteerCenterDuty 1500//中间值
#define SteerSafeTurnDuty 200//边缘值
//舵机默认参数
#define SteerDefaultDuty SteerCenterDuty//开机打角
#define SteerPIDDefaultP 1//舵机默认P
#define SteerPIDDefaultI 1//舵机默认I
#define SteerPIDDefaultD 1//舵机默认D
//舵机限制参数
#define SteerTurnMax (SteerCenterDuty + SteerSafeTurnDuty)//舵机pwm最大值限制
#define SteerTurnMin (SteerCenterDuty - SteerSafeTurnDuty)//舵机pwm最小值限制
#define SteerPidMaxP  1//舵机最大P
#define SteerPidMaxI  1//舵机最大I
#define SteerPidMaxD  1//舵机最大D
#define SteerPidMinP  0//舵机最小P
#define SteerPidMinI  0//舵机最小I
#define SteerPidMinD  0//舵机最小D

/************************************************************************/
/*           数据类型定义                                                  */
/************************************************************************/
typedef enum
{
	SteerDegree0,//0度,居中直行
	SteerDegree1,//1度
	SteerDegree2,//2度
	SteerDegree3,//3度
	SteerDegree4,//4度
	SteerDegree5,//5度
	SteerDegree6,//6度
	SteerDegree7,//7度
	SteerDegree8,//8度
	SteerDegree9,//9度
	SteerDegree10,//10度
	SteerDegree11,//11度
	SteerDegree12,//12度
	SteerDegree13,//13度
	SteerDegree14,//14度
	SteerDegree15,//15度
	SteerDegree16,//16度
	SteerDegree17,//17度
	SteerDegree18,//18度
	SteerDegree19,//19度
	SteerDegree20,//20度
	SteerDegree21,//21度
	SteerDegree22,//22度
	SteerDegree23,//23度
	SteerDegree24,//24度
	SteerDegree25,//25度
	SteerDegree26,//26度
	SteerDegree27,//27度
	SteerDegree28,//28度
	SteerDegree29,//29度
	SteerDegree30,//30度
	SteerDegree31,//31度
	SteerDegree32,//32度
	SteerDegree33,//33度
	SteerDegree34,//34度
	SteerDegree35,//35度
	SteerDegree36,//36度
	SteerDegree37,//37度
	SteerDegree38,//38度
	SteerDegree39,//39度
	SteerDegree40,//40度
	/*
	SteerDegree41,//41度
	SteerDegree42,//42度
	SteerDegree43,//43度
	SteerDegree44,//44度
	SteerDegree45,//45度
	SteerDegree46,//46度
	SteerDegree47,//47度
	SteerDegree48,//48度
	SteerDegree49,//49度
	SteerDegree50,//50度
	SteerDegree51,//51度
	SteerDegree52,//52度
	SteerDegree53,//53度
	SteerDegree54,//54度
	SteerDegree55,//55度
	SteerDegree56,//56度
	SteerDegree57,//57度
	SteerDegree58,//58度
	SteerDegree59,//59度
	SteerDegree60,//60度
	SteerDegree61,//61度
	SteerDegree62,//62度
	SteerDegree63,//63度
	SteerDegree64,//64度
	SteerDegree65,//65度
	SteerDegree66,//66度
	SteerDegree67,//67度
	SteerDegree68,//68度
	SteerDegree69,//69度
	SteerDegree70,//70度
	SteerDegree71,//71度
	SteerDegree72,//72度
	SteerDegree73,//73度
	SteerDegree74,//74度
	SteerDegree75,//75度
	SteerDegree76,//76度
	SteerDegree77,//77度
	SteerDegree78,//78度
	SteerDegree79,//79度
	SteerDegree80,//80度
	SteerDegree81,//81度
	SteerDegree82,//82度
	SteerDegree83,//83度
	SteerDegree84,//84度
	SteerDegree85,//85度
	SteerDegree86,//86度
	SteerDegree87,//87度
	SteerDegree88,//88度
	SteerDegree89,//89度
	SteerDegree90,//90度
	排除过大角度
	*/
	SteerDegreeNum,//成员数
}SteerTurnDegree_e;//转向角度

typedef enum
{
	SteerDirectionLeft,//左转
	SteerDirectionCenter,//直行
	SteerDirectionRight,//右转
}SteerTurnDirection_e;//转向方向



//extern SteerTurnDirection_e CarDirection;

/************************************************************************/
/*         外部函数声明                                               */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
InitRepot_e SteerInit();//舵机初始化，发送默认pwm

//////////////////////////////////////////////////////////////////////////
void SteerTurn(SteerTurnDirection_e direction, SteerTurnDegree_e degree);//转向

//////////////////////////////////////////////////////////////////////////
void StreePidSet(Pid_e steerPid, uint8 steerPidChange);//设定舵机pid参数

SteerTurnDirection_e SteerDirectionSetByAdcOne(struct FLAdc_s adc_s);

#endif//_FL_STEER_
