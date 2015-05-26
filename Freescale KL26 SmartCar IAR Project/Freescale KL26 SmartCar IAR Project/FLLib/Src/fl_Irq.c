
#include "common.h"
#include "fl_irq.h"

static char[100];
/************************************************************************/
/*       �����жϴ�����                                               */
/************************************************************************/
void UartHandler()
{
	////////////////����//////////////////////////////////////////////////////////
	char str[100];
	uint32 num;
	uint16 pidtemp;
	num = uart_querystr(UART0, str, 100);
	

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
	
    MotorCtrl();
	extern uint32 mpwm;
	//printf("$%d,1000,%d,0,0,0,0,0#", Speed.Acturally, mpwm);
	tpm_pulse_clean(TPM2);                                  //����������������ֵ����ʼ�µļ�����
	led_turn(LED3);

	

	PIT_Flag_Clear(PIT0);
}

