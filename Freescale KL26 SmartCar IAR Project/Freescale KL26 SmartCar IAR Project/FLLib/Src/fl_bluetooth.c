
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
/*  �ⲿ���ú���                                                        */
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
/* BlueTooth ���ڳ�ʼ��                              20150107           */
/************************************************************************/
void BludToothUartInit()
{
	FuncLocalShow("BludToothUartInit");
	uart_init(BlueToothUartPort, BlueToothUartBaudRate);

	set_vector_handler(UART0_VECTORn, BlueToothHandler);
}

