
#include "common.h"
#include "fl_irq.h"
#include "fl_Motor.h"
#include "fl_steer.h"

#ifdef MKL26Z4
#include "MKL_uart.h"
#include "MKL_pit.h"
#elif MK60F15
#include "MK60_uart.h"
#include "MK60_pit.h"
#elif MK60DZ10
#include "MK60_uart.h"
#include "MK60_pit.h"
#endif

/************************************************************************/
/*       串口中断处理函数                                               */
/************************************************************************/
void UartHandler()
{
	////////////////串口//////////////////////////////////////////////////////////
	char ch;

	if (uart_query(UART0) == 1)   //接收数据寄存器满
	{
		//用户需要处理接收数据
		uart_getchar(UART0, &ch);                    //无限等待接受1个字节
		uart_putchar(UART0, ch);                    //发送字符串
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void BlueToothHandler()
{
	////////////////串口//////////////////////////////////////////////////////////
	char ch;

	if (uart_query(UART0) == 1)   //接收数据寄存器满
	{
		//用户需要处理接收数据
		uart_getchar(UART0, &ch);                    //无限等待接受1个字节
		uart_putchar(UART0, ch);                    //发送字符串
	}
}

/************************************************************************/
/* PIT0中断函数                                         20150107        */
/************************************************************************/
extern struct MotorSpeed_s Speed;


#define CordLineInOneCircle 500
#define WheelGirth 10
void PIT_IRQHandler(void)
{
	//TpmCountRead();
	Speed.Acturally = tpm_pulse_get(TPM2);
	//Speed.Acturally = (tpm_pulse_get(TPM2) * WheelGirth) / (CordLineInOneCircle * CoderTimeCircle);                         //保存脉冲计数器计算值
	printf("$%d,1000,0,0,0,0,0,0#", Speed.Acturally);

	tpm_pulse_clean(TPM2);                                  //清空脉冲计数器计算值（开始新的计数）
	led_turn(LED3);

	MotorCtrl();

	PIT_Flag_Clear(PIT0);
}

