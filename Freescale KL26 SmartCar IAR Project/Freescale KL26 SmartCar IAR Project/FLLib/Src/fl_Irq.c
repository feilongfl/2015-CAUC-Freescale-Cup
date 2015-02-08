
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
/*       �����жϴ�����                                               */
/************************************************************************/
void UartHandler()
{
	FuncLocalShow("UartHandler");
	////////////////����//////////////////////////////////////////////////////////
	char ch;

	if (uart_query(UART0) == 1)   //�������ݼĴ�����
	{
		//�û���Ҫ�����������
		uart_getchar(UART0, &ch);                    //���޵ȴ�����1���ֽ�
		uart_putchar(UART0, ch);                    //�����ַ���
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void BlueToothHandler()
{
	FuncLocalShow("BlueToothHandle");
	////////////////����//////////////////////////////////////////////////////////
	char ch;

	if (uart_query(UART0) == 1)   //�������ݼĴ�����
	{
		//�û���Ҫ�����������
		uart_getchar(UART0, &ch);                    //���޵ȴ�����1���ֽ�
		uart_putchar(UART0, ch);                    //�����ַ���
	}
}

/************************************************************************/
/* PIT0�жϺ���                                         20150107        */
/************************************************************************/
void PIT_IRQHandler(void)
{
	FuncLocalShow("PIT_IRQHandler");
	//TpmCountRead();
	PIT_Flag_Clear(PIT0);
}

