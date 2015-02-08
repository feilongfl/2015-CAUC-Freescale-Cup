
#include "common.h"
#include "fl_bluetooth.h"
#ifdef MKL26Z4
#include "MKL_uart.h"
#elif MK60F15
#include "MK60_uart.h"
#elif MK60DZ10
#include "MK60_uart.h"
#endif

/************************************************************************/
/*  外部引用函数                                                        */
/************************************************************************/
extern void BlueToothHandler();

/************************************************************************/
/*                                                                      */
/************************************************************************/
void BlueToothShow(char * str)
{
	uart_putstr(BlueToothUartPort, (uint8*)str);
}

/************************************************************************/
/* BlueTooth 串口初始化                              20150107           */
/************************************************************************/
void BludToothUartInit()
{
	FuncLocalShow("BludToothUartInit");
	uart_init(BlueToothUartPort, BlueToothUartBaudRate);

	set_vector_handler(UART0_VECTORn, BlueToothHandler);
}

