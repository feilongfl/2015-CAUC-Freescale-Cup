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
#include "fl_SteerFuzzy.h"

uint16 SpeedForline = 0;//速度

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




/************************************************************************/
/* 控速                                                               */
/************************************************************************/
void SpeedCtrl()
{
//////////////////////////////////////////////////////////////////////////
/*  距离控速                                      */
	
	Speed.Expect = (lostRoad > LostRoadTimesMin) ? FreecaleConfig.Config.Motor.Speed.LostLineSpeed : SpeedForline;
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
#if 0
	extern void DebugAdc();
	DebugAdc();
#endif

	//////////////////////////////////////////////////////////////////////////
	//                       局部变量或结构体                               //
	//////////////////////////////////////////////////////////////////////////
	SpeedForline = FreecaleConfig.Config.Motor.Speed.LineSpeed;
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
		LCDPrint(0, 0, "Car Ready!");


		AdcInit();
		if (FreecaleConfig.Config.Mode.NrfStartCar == On)
		{
			if (FreecaleConfig.Config.CarThis == MyCar1)
			{
				uint8 exitfunc = false;
				LCDPrint(0, LcdLine2, "Press the");
				LCDPrint(LcdLocal2, LcdLine3, "start!");

				while (!exitfunc)
				{
					switch (KeyScanWithoutIrq())//按键检测
					{
					case FLKeyAdcNorExit:
						LcdCls();
						LCDPrint(LcdLocal1, LcdLine1, "Findind Car2!");
						while (NrfSendStr("$", 1) != Nrf_AllGreen)
						{
							led(LED1, LED_ON);
							DELAY_MS(1);
						};
						led(LED1, LED_OFF);
						exitfunc = TRUE;//退出
						break;

					default:
						break;
					}
				}
			}
			else
			{
				LCDPrint(0, LcdLine2, "Wait Command!");
				uint8 strTemp[10];
				while (true)
				{
					if (NrfRecStrCheck(strTemp, 5) != 0)
					{
						if (strTemp)
						{
							break;
						}
					}

					led(LED1, LED_ON);
					DELAY_MS(1);
				} led(LED1, LED_OFF);
			}
#endif//UseAdcNormalizingInit
		}
#if UsePowerOnDelay
		DELAY_MS(2000);
#else
		if (FreecaleConfig.Config.CarDelay > 0)
		{
			LcdCls();
			LCDPrint(0, 0, "wait TimeOut!");
			DELAY_MS(FreecaleConfig.Config.CarDelay * 10);
		}
		LcdCls();
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
	Speed.Expect = SpeedForline;
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

		NumShow3(MotorPid.P, LcdLocal1, LcdLine3);
		NumShow3(MotorPid.I, LcdLocal2, LcdLine3);
		NumShow3(MotorPid.D, LcdLocal3, LcdLine3);

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


