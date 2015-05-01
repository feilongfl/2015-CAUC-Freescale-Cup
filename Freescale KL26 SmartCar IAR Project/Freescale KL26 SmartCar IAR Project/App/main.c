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
	enable_irq(PIT_IRQn);								  //使能PIT0中断
	set_vector_handler(UART0_VECTORn, UartHandler);   // 设置中断服务函数到中断向量表里
	uart_rx_irq_en(UART0);//串口中断
	//uart_rx_irq_en(BlueToothUartPort);//蓝牙串口中断
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
	AdcInit();
	extern struct FLAdc_s AdcMax;
	uint16 * adcMaxAddress = (uint16*)&AdcMax;
	for (uint8 loopTemp = 0; loopTemp < FLAdcMax; loopTemp++)
	{
		*(adcMaxAddress + loopTemp) = 150;
	}
#endif
	//程序循环
	while (1)
	{
		adcn = AdcNormalizing();
		SteerTurnDirection_e turn = SteerDirectionSetByAdcOne(&adcn);
		SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);
		printf("$%d,%d,%d,%d,%d,%d,0,0#",(uint8)turn,(uint8)de,
			adcn.FLAdc0,adcn.FlAdc1,adcn.FLAdc2,adcn.FLAdc3);
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
		
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1500);
 		//DELAY_MS(1000);
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1300);
// 		DELAY_MS(1000);
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1500);
// 		DELAY_MS(1000);
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1700);
// 		DELAY_MS(1000);


		//LcdShowAllData(); 
		//wdog_feed ();
		DELAY_MS(1000);
	}






	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Don't leave main////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


