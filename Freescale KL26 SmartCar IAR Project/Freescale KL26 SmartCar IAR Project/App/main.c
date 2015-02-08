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

	//////////////////////////////////////////////////////////////////////////
	//                       位置提示                                       //
	//////////////////////////////////////////////////////////////////////////
	FuncLocalShow("main");

	

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
	
	//LCDPrint(0, LcdLine2, "飞龙");
	while (1)
	{
		//Hcsr04Read();
		//CoderRead ();



		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1500);
		DELAY_MS(1000);
		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1300);
		DELAY_MS(1000);
		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1500);
		DELAY_MS(1000);
		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1700);
		DELAY_MS(1000);


		//LcdShowAllData(); 
		//wdog_feed ();
		//DELAY_MS(1000);
	}






	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Don't leave main////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


