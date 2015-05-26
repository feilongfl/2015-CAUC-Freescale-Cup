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
/* 全局变量或结构体                                                     */
/************************************************************************/
FLAdcLostLine_e IsLostLine = LostLine;
/************************************************************************/
/*  外部引用函数                                                     */
/************************************************************************/
extern void UartHandler();
/************************************************************************/
/*                       主函数                                         */
/************************************************************************/
void main()
{
	//////////////////////////////////////////////////////////////////////////
	//                       局部变量或结构体                               //
	//////////////////////////////////////////////////////////////////////////
	
	struct FLAdc_s adcn;
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
	
	printf("start");
#if 1
	AdcNormalizingInit();//初始化归一化变量
#else
	LCDPrint(0, 0, "start!");
	AdcInit();
	extern struct FLAdc_s AdcMax;
	uint16 * adcMaxAddress = (uint16*)&AdcMax;
	uint16 adcmaxarr[FLAdcMax] = { 116, 141, 137, 143 };
	for (uint8 loopTemp = 0; loopTemp < FLAdcMax; loopTemp++)
	{
		*(adcMaxAddress + loopTemp) = adcmaxarr[loopTemp];
	}
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
	
#endif
	uint16 spwm = 1500;
	enable_irq(PIT_IRQn);								  //使能PIT0中断
	//程序循环
	while (1)
	{
		adcn = AdcNormalizing();
		SteerTurnDirection_e turn = SteerDirectionSetByAdcOne(&adcn,&IsLostLine);
		SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);
		int32 pidatsteer = SteerCtrlUsePid(de);
		NumShow(ABS(de), 0, 0);

		NumShow(SteerPid.P, LcdLocal1, LcdLine3);
		NumShow(SteerPid.I, LcdLocal2, LcdLine3);
		NumShow(SteerPid.D, LcdLocal3, LcdLine3);
		
		if (IsLostLine == LostLine)
		{
			led(LED0, LED_ON);
			Speed.Expect = 0;
		}
		else//OnLine
		{
			Speed.Expect = 1000;

			led(LED0, LED_OFF);

			if (pidatsteer < -500)
			{
				led(LED2, LED_ON);
				tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + 500);
			}
			else if (pidatsteer > 500)
			{
				led(LED2, LED_ON);
				tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - 500);
			}
			else
			{
				spwm = SteerCenterDuty - pidatsteer;
				led(LED2, LED_OFF);
				tpm_pwm_duty(TpmSteer, TpmSteerCh, spwm);
			}
		}
		

		
		printf("$%d,%d,%d,%d,%d,%d,%d,%d#", (uint8)turn, ABS(de),
			SteerPid.P, SteerPid.I, SteerPid.D, 0
			, pidatsteer, spwm);

		//printf("$%d,%d,%d,0,0,0,0,0#", spwm, ABS(de), pidatsteer);
		DELAY_MS(100);



		//tpm_pwm_duty(TpmMotor, TpmMotorCh0, 0);
		//lptmr_time_start_us();                  //开始计时
		//adcn = AdcNormalizing();
		//adcn = AdcNormalizingWithFitter();
		//uint32 t = lptmr_time_get_us();          //停止计时，获取计时时间
		//DELAY_MS(100);
		//printf("\n%d\n", t);

		// 		printf("$%d,%d,%d,%d,0,0,0,0#",
		// 			adcn.FLAdc0, adcn.FlAdc1, adcn.FLAdc2, adcn.FLAdc3);
		//Hcsr04Read();
		//CoderRead ();
		//led_turn(LED3);

		//LcdShowAllData(); 
		//wdog_feed ();
		//DELAY_MS(5000);
	}






	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Don't leave main////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


