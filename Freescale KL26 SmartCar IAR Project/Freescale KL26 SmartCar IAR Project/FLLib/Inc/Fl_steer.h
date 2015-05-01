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

#define SteerAngleProtectRange 500//左右电感偏差值在此范围内认定为直行
#define LostLineAdcMin 200//所有电感归一化后数值少于此值认定为丢线

/************************************************************************/
/*           数据类型定义                                                  */
/************************************************************************/
typedef uint8 SteerDeviationDegree_e;//转向角度

typedef enum
{
	SteerDirectionLeft,//左转
	SteerDirectionCenter,//直行
	SteerDirectionRight,//右转
}SteerTurnDirection_e;//转向方向



extern SteerTurnDirection_e CarDirection;

/************************************************************************/
/*         外部函数声明                                               */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
InitRepot_e SteerInit();//舵机初始化，发送默认pwm

//////////////////////////////////////////////////////////////////////////
void SteerTurn(SteerTurnDirection_e direction, SteerDeviationDegree_e degree);//转向

//////////////////////////////////////////////////////////////////////////
void StreePidSet(Pid_e steerPid, uint8 steerPidChange);//设定舵机pid参数

SteerTurnDirection_e SteerDirectionSetByAdcOne(struct FLAdc_s * adc_s);
SteerDeviationDegree_e SteerDeviationDegreeSetByAdc(struct FLAdc_s * adc_s);
#endif//_FL_STEER_
