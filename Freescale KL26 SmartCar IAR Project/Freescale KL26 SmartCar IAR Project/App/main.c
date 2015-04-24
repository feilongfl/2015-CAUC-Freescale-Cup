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

	while (!nrf_init())                  //初始化NRF24L01+ ,等待初始化成功为止
	{
		printf("\n  NRF与MCU连接失败，请重新检查接线。\n");
	}

	printf("\n      NRF与MCU连接成功！\n");

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
	//AdcNormalizingInit();//初始化归一化变量
	nrf_init();
	uint8 * msg = "hello";
	//程序循环
	while (1)
	{
		//Hcsr04Read();
		//CoderRead ();
		led_turn(LED3);
		sprintf((char *)buff, "%s", msg);         //把str和i合并成一个字符串到buff里，再进行发送
		if (nrf_tx(buff, DATA_PACKET) == 1)         //发送一个数据包：buff（包为32字节）
		{
			//等待发送过程中，此处可以加入处理任务

			while (nrf_tx_state() == NRF_TXING);         //等待发送完成

			if (NRF_TX_OK == nrf_tx_state())
			{
				printf("\n发送成功");
			}
			else
			{
				printf("\n发送失败");
			}
		}
		else
		{
			printf("\n发送失败");
		}

// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1500);
 		DELAY_MS(1000);
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1300);
// 		DELAY_MS(1000);
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1500);
// 		DELAY_MS(1000);
// 		tpm_pwm_duty(TpmSteer, TpmSteerCh, 1700);
// 		DELAY_MS(1000);


		//LcdShowAllData(); 
		//wdog_feed ();
		//DELAY_MS(1000);
	}






	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Don't leave main////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


