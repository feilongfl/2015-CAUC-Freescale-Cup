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

//舵机限制参数
#define SteerTurnMax (SteerCenterDuty + SteerSafeTurnDuty)//舵机pwm最大值限制
#define SteerTurnMin (SteerCenterDuty - SteerSafeTurnDuty)//舵机pwm最小值限制

#define SteerAngleProtectRange 200//左右电感偏差值在此范围内认定为直行
#define LostLineAdcMin 500//所有电感归一化后数值少于此值认定为丢线

/************************************************************************/
/*           数据类型定义                                                  */
/************************************************************************/
//#define SteerDegAbs
#ifdef SteerDegAbs
typedef uint8 SteerDeviationDegree_e;//转向角度
#else
typedef int16 SteerDeviationDegree_e;//转向角度
#endif

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
//void SteerTurn(SteerTurnDirection_e direction, SteerDeviationDegree_e degree);//转向

//////////////////////////////////////////////////////////////////////////
void StreePidSet(Pid_e steerPid, uint8 steerPidChange);//设定舵机pid参数

SteerTurnDirection_e SteerDirectionSetByAdcOne(struct FLAdc_s * adc_s,FLAdcLostLine_e * lostLine);
SteerDeviationDegree_e SteerDeviationDegreeSetByAdc(struct FLAdc_s * adc_s);
void SteerVagueCtrl(int16 offset);

void SteerFuzzyDomainScan();
#endif//_FL_STEER_
