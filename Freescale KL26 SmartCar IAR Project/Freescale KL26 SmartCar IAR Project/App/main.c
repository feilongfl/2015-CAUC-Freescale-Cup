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

/************************************************************************/
/*                                 功能开关                             */
/************************************************************************/
#define UseAdcNormalizingInit		DoNotUseIt//开机归一化使能
#define UseEndLine					DoNotUseIt
#define UsePowerOnDelay				UseIt
#define UseEeprom					DoNotUseIt
#define UseLostRoadStop				UseIt

#define SpeedForTest				500

/************************************************************************/
/* 全局变量或结构体                                                     */
/************************************************************************/
uint8 lostRoad = 0;
/************************************************************************/
/*  外部引用函数                                                     */
/************************************************************************/
extern void UartHandler();


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
void VagueCtrl(int16 offset)
{
	offset = RANGE(offset, 59, -59) + 60;//限幅+提升原点
	
	offset /= 10;//偏差模糊化
	uint16 sum = 0;
	uint16 pwm = 0;

	if (!RANGEQurr(offset, 8, 5))//不直
	{
		for (uint8 i = 0; i < SteerGears;i++)//求分母
		{
			sum += SteerCRI[i][offset];
			sum += SteerCRI[i][offset + 1];
		}

		for (uint8 i = 0; i < SteerGears; i++)//求pwm
		{
			pwm += SteerPwmArr[i] * (SteerCRI[i][offset] + SteerCRI[i][offset + 1]) / sum;
		}
	}
	else//差不多挺直的
	{
		pwm = SteerCenterDuty;
	}
	tpm_pwm_duty(TpmSteer, TpmSteerCh, pwm);
}
//////////////////////////////////////////////////////////////////////////

void SteerCtrl()
{
	struct FLAdc_s adcn;
	FLAdcLostLine_e IsLostLine = LostLine;

	adcn = AdcNormalizing();//获取归一化电感值
	SteerTurnDirection_e turn = SteerDirectionSetByAdcOne(&adcn, &IsLostLine);
	SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);
	//int32 pidatsteer = SteerCtrlUsePid(de);
	NumShow(ABS(de), 0, 0);

	if (IsLostLine == LostLine)//丢线
	{
		led(LED0, LED_ON);
#if UseLostRoadStop
		Speed.Expect = (lostRoad > 10) ? 0 : SpeedForTest;
		lostRoad = (lostRoad > 10) ? 255 : lostRoad++;
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
		VagueCtrl(de);
		led(LED0, LED_OFF);

		
	}
}



/************************************************************************/
/*                       主函数                                         */
/************************************************************************/
void main()
{
	//////////////////////////////////////////////////////////////////////////
	//                       局部变量或结构体                               //
	//////////////////////////////////////////////////////////////////////////
	ConfigInit();
	
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

	
	

	uint16 spwm = SteerCenterDuty;
	Speed.Expect = SpeedForTest;
	enable_irq(PIT_IRQn);								  //使能PIT0中断
	//程序循环
	while (1)
	{
		SteerCtrl();

#if 1
		
#else

		
		NumShow16(Speed.Expect, LcdLocal1, LcdLine1);
		NumShow16(Speed.Acturally, LcdLocal1, LcdLine2);
		
		NumShow(MotorPid.P, LcdLocal1, LcdLine3);
		NumShow(MotorPid.I, LcdLocal2, LcdLine3);
		NumShow(MotorPid.D, LcdLocal3, LcdLine3);
		
#endif
		DELAY_MS(100);
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Don't leave main////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


