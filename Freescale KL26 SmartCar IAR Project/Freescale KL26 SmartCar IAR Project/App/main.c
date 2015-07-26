/*!
*
* @file       main.c
* @brief      飞思卡尔主程序
* @author     飞龙
* @version    v0.1
* @date       2015-1-7
*/
/************************************************************************/
/* 文件包含                                                             */
/************************************************************************/
#include "main.h"


uint32 CarDistance = 0;
uint8 NrfBuff[DATA_PACKET];


#if UseMpu6050ChangeSpeed
Mpu6050Data mpu6050Data;
#endif

/************************************************************************/
/* 全局变量或结构体                                                     */
/************************************************************************/
uint8 lostRoad = 0;
/************************************************************************/
/*  外部引用函数                                                     */
/************************************************************************/
extern void UartHandler();



void SteerCtrl()
{
	struct FLAdc_s adcn;
	FLAdcLostLine_e IsLostLine = LostLine;

	adcn = AdcNormalizing();//获取归一化电感值
	SteerTurnDirection_e turn = SteerDirectionSetByAdcOne(&adcn, &IsLostLine);
	SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);

	uint8 time = 0;
	int8 turnTemp = 0;
	//int32 pidatsteer = SteerCtrlUsePid(de);
	NumShow(ABS(de), 0, 0);

	if (IsLostLine == LostLine)//丢线
	{
		led(LED0, LED_ON);
#if UseLostRoadStop
		Speed.Expect = (lostRoad > 10) ? 0 : SpeedForTest;
		lostRoad = (lostRoad > 10) ? 255 : lostRoad+1;

#define SteerLostLinetimeMax 10//直角弯道判断次数
		if (lostRoad > 10)
		{
			if (ABS(adcn.AdcVertical.Adc0 - adcn.AdcVertical.Adc1) > 80)//直角弯道判断最小差值
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
					time = 0;
				}
				else//没丢线，清楚标志
				{
					time = 0;
				}
			}
		}
#endif//UseLostRoadStop
		switch (turn)
		{
		case SteerDirectionLeft:
			tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + 500);
			break;

		case SteerDirectionRight:
			tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - 500);
			break;

		case SteerDirectionCenter:
			led(LED2, LED_ON);
			//直角
			break;

		default:
			break;
		}
	}
	else//OnLine
	{
#if UseLostRoadStop
		lostRoad = 0;
		Speed.Expect = SpeedForTest;
#endif//UseLostRoadStop
		SteerVagueCtrl(de);
		led(LED0, LED_OFF);

		
	}
}

/************************************************************************/
/* 控速                                                               */
/************************************************************************/
void SpeedCtrl()
{
//////////////////////////////////////////////////////////////////////////
/*  距离控速                                      */
	Speed.Expect = SpeedForTest;
#if UseDistanceChangeSpeed
	#warning please change these num
	if (CarDistance < 100)//only for test,don't forget change this num
	{
#if Car == Car1
		Speed.Expect += 100;//num is for test,car1
#elif Car == Car2
		Speed.Expect -= 100;//num is for test,car2
#endif
	}
	else if (CarDistance > 200)//num is for test
	{
#if Car == Car1
		Speed.Expect -= 100;//num is for test,car1
#elif Car == Car2
		Speed.Expect += 100;//num is for test,car2
#endif
	}
	else
	{
		//Speed.Expect = SpeedForTest;
	}

#endif //UseDistanceChangeSpeed

/*mpu6050 坡道控速*/
#if UseMpu6050ChangeSpeed
	mpu6050Data = Mpu6050Read();
	#warning please test these line
	if (mpu6050Data.accel.z > 10)
	{
		Speed.Expect += 100;
	}
	else if (mpu6050Data.accel.z < 10)
	{
		Speed.Expect -= 100;
	}
	else
	{

	}
#endif //UseMpu6050ChangeSpeed
}


/************************************************************************/
/*                       主函数                                         */
/************************************************************************/
void main()
{
	//////////////////////////////////////////////////////////////////////////
	//                       局部变量或结构体                               //
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	//                       位置提示                                       //
	//////////////////////////////////////////////////////////////////////////
	/************************************************************************/
	/* 开中断                                                               */
	/************************************************************************/
	
	set_vector_handler(UART0_VECTORn, UartHandler);   // 设置中断服务函数到中断向量表里
	uart_rx_irq_en(UART0);//串口中断
	FLKeyIrqEnable();
        //wdog_init (1000);//初始化看门狗
        //wdog_enable ();
	//////////////////////////////////////////////////////////////////////////
	//                       用户操作                                       //
	//////////////////////////////////////////////////////////////////////////
#if UseEndLine
	switch (FreecaleConfig.Config.CarState)
	{
	case CarStandby:
#endif//UseEndLine
		printf("start");
#if UseAdcNormalizingInit
		AdcNormalizingInit();//初始化归一化变量
#else//UseAdcNormalizingInit
		LCDPrint(0, 0, "start!");
		AdcInit();
		uint8 exitfunc = false;

		while (!exitfunc)
		{
			switch (KeyScanWithoutIrq())//按键检测
			{
			case FLKeyAdcNorExit:
				exitfunc = TRUE;//退出
				break;

			default:
				break;
			}
		}
#endif//UseAdcNormalizingInit

#if UsePowerOnDelay
		DELAY_MS(2000);
#endif//UsePowerOnDelay


		//////////////////////////////////////////////////////////////////////////
		//终点线
#if UseEndLine
		break;

	case CarRunning:
		break;

	case CarFinish:
		LCDPrint(0, 0, "Finish!");
		break;

	default:
		break;
	}
#endif//UseEndLine

	
	

	//uint16 spwm = SteerCenterDuty;
	Speed.Expect = SpeedForTest;
	enable_irq(PIT_IRQn);								  //使能PIT0中断
	//程序循环
	while (1)
	{
		//////////////////////////////////////////////////////////////////////////
		//舵机控制
		SteerCtrl();

#if 1
		
#else
		///lcd show
		
		NumShow16(Speed.Expect, LcdLocal1, LcdLine1);
		NumShow16(Speed.Acturally, LcdLocal1, LcdLine2);
		
		NumShow(MotorPid.P, LcdLocal1, LcdLine3);
		NumShow(MotorPid.I, LcdLocal2, LcdLine3);
		NumShow(MotorPid.D, LcdLocal3, LcdLine3);
		
#endif


		SpeedCtrl();


		//////////////////////////////////////////////////////////////////////////
		//nrf
#if UseNrfSendOrReceiveMsg
		//NrfErrorType_e nrfErr;
#if Car == Car1
		if (NrfRecStrCheck(NrfBuff, 3))
		{
#if UseCar2NrfSendDistance
			if (NrfBuff[0] == '$')//超声波识别符
			{
				uint8 i = 0;
				while (NrfBuff[i + 1] != '#')//求字符串长度
				{
					if (NrfBuff[i + 1] == '\0')//error
					{
						goto exitthismainloop;//没辙了，我真不想这么写，实在不能再循环了，变量太多了
						//break;
					}
					i++;
				}

				uint32 dis = 0;
				for (uint8 j = 0; j < i;j++)//求数值
				{
					dis += POW((uint32)(NrfBuff[j + 1] - '0'), i - j);
				}
			}
#endif
		}
#elif Car == Car2
#if UseCar2NrfSendDistance
		sprintf(NrfBuff,"$%d#",CarDistance);
		NrfSendStrCheck(NrfBuff,sizeof(NrfBuff) / sizeof(uint8),3);
#endif
#else//error
#error please select you car
#endif //car switch
#endif//UseNrfSendOrReceiveMsg

		//////////////////////////////////////////////////////////////////////////
exitthismainloop:
		//延迟，控制周期
		DELAY_MS(20);
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Don't leave main////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


