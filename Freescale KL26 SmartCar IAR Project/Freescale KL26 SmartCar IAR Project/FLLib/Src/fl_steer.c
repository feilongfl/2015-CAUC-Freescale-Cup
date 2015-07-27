#include "Fl_steer.h"
#include "fl_config.h"


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
	SteerPidInit();
	SteerqPID_Init();
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


void SteerCtrl_1()
{
	struct FLAdc_s adcn;
	FLAdcLostLine_e IsLostLine = LostLine;

	adcn = AdcNormalizing();//获取归一化电感值
	SteerTurnDirection_e turn = SteerDirectionSetByAdcOne(&adcn, &IsLostLine);
	SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);

	static uint8 time = 0;
	static int8 turnTemp = 0;
	//int32 pidatsteer = SteerCtrlUsePid(de);
	NumShow3(ABS(de), 0, 0);

	if (IsLostLine == LostLine)//丢线
	{
		led(LED0, LED_ON);
#if UseLostRoadStop
		lostRoad = (lostRoad > LostRoadTimesMin) ? 255 : lostRoad + 1;

#define SteerLostLinetimeMax 3//直角弯道判断次数
		if (
			(ABS(adcn.AdcVertical.Adc0 - adcn.AdcVertical.Adc1) > 80)
#define AdcVertialLostMin 100
			&& (adcn.AdcVertical.Adc0 > AdcVertialLostMin
			|| adcn.AdcVertical.Adc0 > AdcVertialLostMin)
			)//直角弯道判断最小差值
		{
			turnTemp += ((adcn.AdcVertical.Adc0 > adcn.AdcVertical.Adc1) ? SteerDirectionLeft : SteerDirectionRight) - 1;//累加方向临时变量
			if (time++ > SteerLostLinetimeMax)//计数，判断
			{
				if (RANGEQurr(turnTemp, SteerLostLinetimeMax / 3, -SteerLostLinetimeMax / 3))//中间
				{
					turn = SteerDirectionCenter;
				}
				else if (turnTemp < 0)
				{
					turn = SteerDirectionRight;
				}
				else
				{
					turn = SteerDirectionLeft;
				}

				switch (turn)
				{
				case SteerDirectionLeft:
					tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + SteerSafeTurnDuty);
					break;

				case SteerDirectionRight:
					tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - SteerSafeTurnDuty);
					break;

				case SteerDirectionCenter:
					led(LED2, LED_ON);
					//直角
					break;

				default:
					break;
				}
				//while (1);

				SpeedForline = FreecaleConfig.Config.Motor.Speed.TurnSpeed;//减速

				time = SteerLostLinetimeMax + 1;
				turnTemp = 0;
			}
			else
			{
				DELAY_MS(1);
				SteerCtrl_1();
				return;
			}

		}
		else//不是直角弯，清楚标志
		{
			time = 0;
			switch (turn)
			{
			case SteerDirectionLeft:
				tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + SteerSafeTurnDuty);
				break;

			case SteerDirectionRight:
				tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - SteerSafeTurnDuty);
				break;

			case SteerDirectionCenter:
				led(LED2, LED_ON);
				//直角
				break;

			default:
				break;
			}

		}
#endif//UseLostRoadStop
	}
	else//OnLine
	{
#if UseLostRoadStop
		lostRoad = 0;
		Speed.Expect = SpeedForline;
#endif//UseLostRoadStop
		SteerVagueCtrl(de);
		led(LED0, LED_OFF);


	}
}

void SteerCtrl_2()
{
	struct FLAdc_s adcn;
	FLAdcLostLine_e IsLostLine = LostLine;

	adcn = AdcNormalizing();//获取归一化电感值
	SteerTurnDirection_e turn = SteerDirectionSetByAdcOne(&adcn, &IsLostLine);
	SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);

	static uint8 time = 0;
	static int8 turnTemp = 0;
	//int32 pidatsteer = SteerCtrlUsePid(de);
	NumShow3(ABS(de), 0, 0);

	if (IsLostLine == LostLine)//丢线
	{
		led(LED0, LED_ON);
#if UseLostRoadStop
		lostRoad = (lostRoad > LostRoadTimesMin) ? 255 : lostRoad + 1;

#define SteerLostLinetimeMax 3//直角弯道判断次数
		if (
			(ABS(adcn.AdcVertical.Adc0 - adcn.AdcVertical.Adc1) > 80)
#define AdcVertialLostMin 100
			&& (adcn.AdcVertical.Adc0 > AdcVertialLostMin
			|| adcn.AdcVertical.Adc0 > AdcVertialLostMin)
			)//直角弯道判断最小差值
		{
			turnTemp += ((adcn.AdcVertical.Adc0 > adcn.AdcVertical.Adc1) ? SteerDirectionLeft : SteerDirectionRight) - 1;//累加方向临时变量
			if (time++ > SteerLostLinetimeMax)//计数，判断
			{
				if (RANGEQurr(turnTemp, SteerLostLinetimeMax / 3, -SteerLostLinetimeMax / 3))//中间
				{
					turn = SteerDirectionCenter;
				}
				else if (turnTemp < 0)
				{
					turn = SteerDirectionRight;
				}
				else
				{
					turn = SteerDirectionLeft;
				}

				switch (turn)
				{
				case SteerDirectionLeft:
					tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + SteerSafeTurnDuty);
					break;

				case SteerDirectionRight:
					tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - SteerSafeTurnDuty);
					break;

				case SteerDirectionCenter:
					led(LED2, LED_ON);
					//直角
					break;

				default:
					break;
				}
				//while (1);

				SpeedForline = FreecaleConfig.Config.Motor.Speed.TurnSpeed;//减速

				time = SteerLostLinetimeMax + 1;
				turnTemp = 0;
			}
			else
			{
				DELAY_MS(1);
				SteerCtrl_1();
				return;
			}

		}
		else//不是直角弯，清楚标志
		{
			time = 0;
			switch (turn)
			{
			case SteerDirectionLeft:
				tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + SteerSafeTurnDuty);
				break;

			case SteerDirectionRight:
				tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - SteerSafeTurnDuty);
				break;

			case SteerDirectionCenter:
				led(LED2, LED_ON);
				//直角
				break;

			default:
				break;
			}

		}
#endif//UseLostRoadStop
	}
	else//OnLine
	{
#if UseLostRoadStop
		lostRoad = 0;
		Speed.Expect = SpeedForline;
#endif//UseLostRoadStop
		int32 pwm = SteerCtrlUsePid(de);
		tpm_pwm_duty(TpmSteer, TpmSteerCh, pwm);
		led(LED0, LED_OFF);


	}
}


void SteerCtrl()
{
	switch (FreecaleConfig.Config.Steer.SteerCtrlMethod)
	{
	case SteerCtrlMethod_Fuzzy:
		SteerCtrl_1();
		break;

	case SteerCtrlMethod_Pid:
		SteerCtrl_2();
		break;

	default:
		break;
	}
}

