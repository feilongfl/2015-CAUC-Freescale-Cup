
#include "common.h"
#include "fl_irq.h"

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
	FuncLocalShow("UartHandler");
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
	FuncLocalShow("BlueToothHandle");
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
void PIT_IRQHandler(void)
{
	FuncLocalShow("PIT_IRQHandler");
	//TpmCountRead();
	PIT_Flag_Clear(PIT0);
}

