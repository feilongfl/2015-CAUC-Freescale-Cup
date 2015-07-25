#include "common.h"
#include "include.h"
#include "fl_include.h"



/************************************************************************/
/*                                 功能开关                             */
/************************************************************************/
#define UseAdcNormalizingInit		DoNotUseIt//开机归一化使能
#define UseEndLine					DoNotUseIt//终点线
#define UsePowerOnDelay				UseIt//开车延时
#define UseEeprom					DoNotUseIt//配置存储
#define UseLostRoadStop				UseIt//丢线停止
#define UseMpu6050ChangeSpeed		DoNotUseIt//陀螺仪控速
#define UseDistanceChangeSpeed		DoNotUseIt//距离控速
#define UseSoundSpeedByTemperature	DoNotUseIt//超声波温度补偿
#define UseNrfSendOrReceiveMsg		UseIt
#define UseCar2NrfSendDistance		UseIt
#define UseCar1NrfSendAdc			UseIt

#define SpeedForTest				700//测试速度

#define Car1						1
#define Car2						2
#define Car							Car1

