
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
/*       �����жϴ�����                                               */
/************************************************************************/
void UartHandler()
{
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
extern struct MotorSpeed_s Speed;


#define CordLineInOneCircle 500
#define WheelGirth 10
void PIT_IRQHandler(void)
{
	//TpmCountRead();
	Speed.Acturally = tpm_pulse_get(TPM2);
	//Speed.Acturally = (tpm_pulse_get(TPM2) * WheelGirth) / (CordLineInOneCircle * CoderTimeCircle);                         //�����������������ֵ
	printf("$%d,1000,0,0,0,0,0,0#", Speed.Acturally);

	tpm_pulse_clean(TPM2);                                  //����������������ֵ����ʼ�µļ�����
	led_turn(LED3);

	MotorCtrl();

	PIT_Flag_Clear(PIT0);
}

