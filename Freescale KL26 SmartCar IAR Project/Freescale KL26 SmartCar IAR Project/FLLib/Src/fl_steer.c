#include "Fl_steer.h"



SteerTurnDirection_e CarDirection = SteerDirectionCenter;//历史方向，丢线准备
#define SteerDegreeNum 50//定义角度范围

uint16 SteerDuty[SteerDegreeNum] = {
#ifdef _FL_VISUAL_STUDIO_
#pragma region 舵机打角数组
#endif
	#warning 请设置舵机打角值数组
	0,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
#ifdef _FL_VISUAL_STUDIO_
#pragma endregion 舵机打角数组
#endif 
};//舵机打角值数组

InitRepot_e SteerInit()
{
	tpm_pwm_init(TpmSteer, TpmSteerCh, TpmSteerFreq, SteerDefaultDuty);
	return InitAllGreen;
}

// void SteerTurn(SteerTurnDirection_e direction, SteerDeviationDegree_e degree)
// {
// 	ASSERT(SteerDuty[degree] <= SteerTurnMax);//检测舵机打角数据是否合法
// 
// 	switch (direction)
// 	{
// 	case SteerDirectionLeft:
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - SteerDuty[degree]);
// 		break;
// 
// 	case SteerDirectionCenter:
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty);
// 		break;
// 
// 	case SteerDirectionRight:
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + SteerDuty[degree]);
// 		break;
// 
// 	default:
// 		ASSERT(TRUE);
// 		break;
// 	}
// }

void StreePidSet(Pid_e steerPid, uint8 steerPidChange)
{
	ASSERT(steerPidChange <= PidPrecision);//数值应小于pid精度
	switch (steerPid)
	{
#warning todo
	case Kp:
		//SteerPid.P = steerPidChange;
		break;

	case Ki:
		//SteerPid.I = steerPidChange;
		break;

	case Kd:
		//SteerPid.D = steerPidChange;
		break;

	default:
		ASSERT(TRUE);
		break;
	}
}

static SteerTurnDirection_e steerDirectionSetBySum(int32 sum)
{
	sum /= 5;//这个也算是滤波吧
#if 0
	if (sum < -SteerAngleProtectRange / 5)
	{
		return SteerDirectionRight;
	}
	else if (sum > SteerAngleProtectRange / 5)
	{
		return SteerDirectionLeft;
	}
	else
	{
		return SteerDirectionCenter;
	}
#else
	return (sum > 0) ? SteerDirectionLeft : SteerDirectionRight;
#endif
}


//////////////////////////////////////////////////////////////////////////
//根据adc计算车辆方向
SteerTurnDirection_e SteerDirectionSetByAdcOne(struct FLAdc_s * adc_s, FLAdcLostLine_e * lostLine)
{
	uint16 * adc_addr = (uint16*)adc_s;
	int32 sum = 0;
	FLAdcLostLine_e lostLineTemp = TRUE;

	for (uint8 adcTemp = FLAdcMax; adcTemp > FLAdcMax / 2;adcTemp--)
	{
		sum += *(adc_addr + FLAdcMax - adcTemp);//计算ad左-ad右
		sum -= *(adc_addr + adcTemp - 1);
		lostLineTemp &= (*(adc_addr + FLAdcMax - adcTemp) > LostLineAdcMin) ? false : true;//判断丢线
		lostLineTemp &= (*(adc_addr + adcTemp - 1) > LostLineAdcMin) ? false : true;
	}

	*lostLine = lostLineTemp;

	switch (lostLineTemp)
	{
	case OnLine:
		return CarDirection = steerDirectionSetBySum(sum);
		break;

	case LostLine:
		return CarDirection;
		break;

	default:
		ASSERT(true);
		return CarDirection;//抑制编译时警告
		break;
	}
	
}

SteerDeviationDegree_e SteerDeviationDegreeSetByAdc(struct FLAdc_s * adc_s)
{
	uint16 * adc_addr = (uint16*)adc_s;
	int32 deviation = 0;
	int32 sum = 0;

	for (uint8 adcTemp = FLAdcMax; adcTemp > FLAdcMax / 2; adcTemp--)
	{
		deviation += *(adc_addr + FLAdcMax - adcTemp);//计算ad左-ad右
		deviation -= *(adc_addr + adcTemp - 1);
	}

#ifdef SteerDegAbs
	deviation = ABS(deviation);
#endif

	for (uint8 adcTemp = 0; adcTemp < FLAdcMax; adcTemp++)
	{
		sum += *(adc_addr + adcTemp);//计算ad左+ad右
	}

#if ((FLAdcMax % 2) == 1)
	sum -= *(adc_addr + (uint8)(FLAdcMax / 2) );//奇数个电感时减去中间
#endif

	//网上找的公式，据说是官方的解决方案
	//（ad左-ad右） / （ad左 + ad右） * 100
	return (SteerDeviationDegree_e)((deviation * 100 / sum));
}




//////////////////////////////////////////////////////////////////////////
//舵机模糊控制算法
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*语言变量指表*/
//电感偏差变化范围max = 63
//丢线前偏差最大值max=44
//
//模糊化控制偏差范围-6~6
#define SteerOffSetSum 13
//参考其他方案和以前分档思想，暂定7档
#define SteerGears 7
#warning 论域在不同环境下是不同的，开机时需要扫描，进行类似归一化处理
//偏差论域
#define OffSetMax	59
//原点提升值
#define ZeroPointUp (OffSetMax + 1)
//偏差变化率论域
#define ErrorChangeSpeedMax	6

//偏差变化率
int8 LastError = 0;

//偏差变化量计算表
int8 SteerCtrlQurr[SteerOffSetSum][2 * ErrorChangeSpeedMax + 1] =
{
	6, 5, 6, 5, 6, 6, 4, 4, 3, 2, 1, 1, 0,
	6, 5, 5, 5, 5, 5, 5, 4, 3, 3, 2, 1, 0,
	6, 5, 6, 5, 6, 5, 5, 4, 4, 2, 1, 0, 0,
	5, 5, 5, 5, 5, 5, 4, 4, 3, 3, 1, 0, -1,
	5, 4, 4, 3, 3, 3, 2, 0, 0, -2, -2, -3, -3,
	4, 4, 4, 4, 3, 3, 0, 0, -2, -3, -3, -4, -4,
	4, 4, 3, 3, 3, 0, 0, 0, -1, -3, -3, -3, -5,
	3, 3, 3, 1, 0, 0, 0, -3, -3, -4, -4, -5, -5,
	3, 2, 2, 2, 0, 0, -2, -3, -3, -3, -4, -5, -5,
	2, 1, 0, 0, -1, -3, -3, -4, -4, -4, -5, -5, -5,
	0, 0, 0, -2, -3, -3, -4, -4, -5, -5, -5, -6, -6,
	0, 0, -1, -3, -3, -3, -5, -5, -5, -5, -5, -6, -6,
	0, 0, -2, -3, -3, -4, -4, -5, -5, -6, -6, -6, -6
};

//偏差语言变量值表
//整型化所有数据所有数字乘8
char SteerCRI[SteerGears][SteerOffSetSum] = {
	8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 4, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 4, 8, 4, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 4, 8, 4, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 4, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8,
};
//舵机pwm数组
int16 SteerPwmArr[SteerGears] = {
#if 1
	1000, 1200, 1400, 1500, 1600, 1800, 2000
#elif 0
	- 550, -300, -100, 0, 100, 300, 500
#else
	1000, 1167, 1333, 1500, 1667, 1833, 2000
#endif
};
/************************************************************************/
//offset:偏差
void SteerVagueCtrl(int16 offset)
{
	uint16 sum = 0;
	uint16 pwm = 0;
	int8 errorChanngeSpeed = 0;
	uint8 errQurr = 0;

	offset = RANGE(offset, OffSetMax, -OffSetMax) + ZeroPointUp;//限幅+提升原点

	offset /= 10;//偏差模糊化
	errorChanngeSpeed = RANGE(offset - LastError, ErrorChangeSpeedMax, -ErrorChangeSpeedMax) + ErrorChangeSpeedMax;//偏差变化率，限幅在论域内，提升原点
	LastError = offset;//保存偏差
	//offset = SteerDirection[offset][errorChanngeSpeed];

	printf("offset:%d\n", offset);

	if (!RANGEQurr(offset, 8, 5))//不直
	{
		//利用error and errorchange计算控制量
		errQurr = SteerCtrlQurr[offset][errorChanngeSpeed] + 6;//查表，提升原点
		//重心法解模糊
		for (uint8 i = 0; i < SteerGears; i++)//求分母
		{
			sum += SteerCRI[i][offset];
			sum += SteerCRI[i][offset + 1];
		}

		for (uint8 i = 0; i < SteerGears; i++)//求pwm
		{
			pwm += SteerPwmArr[i] * (SteerCRI[i][offset] + SteerCRI[i][offset + 1]) / sum;
		}
		//Speed.Expect = 500;//悠着点
	}
	else//差不多挺直的，冲啊！！！！！
	{
		pwm = SteerCenterDuty;
		//Speed.Expect = 1000;//飞吧
	}
	//pwm = RANGE(pwm, SteerPwmArr[SteerGears - 1], SteerPwmArr[0]);//限制一下
	tpm_pwm_duty(TpmSteer, TpmSteerCh, pwm);
}
//////////////////////////////////////////////////////////////////////////

