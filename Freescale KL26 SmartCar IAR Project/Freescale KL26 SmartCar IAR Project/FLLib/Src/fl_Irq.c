
#include "common.h"
#include "fl_irq.h"

static uint8 uartCmdLocal = 0;
static char uartCmdBuff[100];
UartCmdAvailable uartCmdAvailable = NotAvailable;

static void pidCmdAnalyze(char * cmd, uint8 cmdLen,void (*func)(Pid_e pidType,uint16 exData))
{
	uint16 cData = 0;
	for (uint8 i = 1; i < cmdLen;i++)
	{
		cData += (cmd[i] - 48) * (cmdLen - i);
	}
	switch (cmd[0])
	{
	case 'P':
		func(Kp, cData);
		break;

	case 'I':
		func(Ki, cData);
		break;

	case 'D':
		func(Kd, cData);
		break;
		
	default:
		printf("error\n");
		break;
	}
}

static void uartCmdAnalyze(char * cmd, int8 cmdLen)
{
	//�ֲ��������洢����λ��
	uint8 cmdReadLocal = 1;
	//���ԣ�����ǰ׺
	ASSERT(cmd[0] != '$');

	//�ж�
	switch (cmd[1])
	{
	case 'S':
		pidCmdAnalyze(cmd + 2, cmdLen - 2, SteerPidSet);
		break;

	case 'M':
		pidCmdAnalyze(cmd + 2, cmdLen - 2, MotorPidSet);
		break;

	case 'C':
		break;

	default:
		printf("error!\n");
		break;
	}
}

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
	
	if (num)
	{
		for (uint8 local = 0; local < num;local++)
		{
			if (str[local] == '$')
			{
				uartCmdLocal = 0;
				uartCmdAvailable = Receiving;
			}
			else if (str[local] == '#')
			{
				uartCmdAvailable = Available;
			}
			
			if (uartCmdLocal > UartCmdLostEndLen)
			{
				uartCmdAvailable = NotAvailable;
			}

			if (uartCmdAvailable == Available)
			{
				// TODO: �����
				uartCmdAnalyze(str, uartCmdLocal);
				//////////////////////////////////////////////////////////////////////////
				uartCmdLocal = 0;
				uartCmdAvailable = NotAvailable;
				break;
			}

			if (uartCmdAvailable = Receiving)
			{
				uartCmdBuff[uartCmdLocal++] = str[local];
			}
		}
	}

}

void UartInit()
{
	for (uint8 i = 0; i < 100;i++)
	{
		uartCmdBuff[i] = '\0';
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
	
    MotorCtrl();
	extern uint32 mpwm;
	//printf("$%d,1000,%d,0,0,0,0,0#", Speed.Acturally, mpwm);
	tpm_pulse_clean(TPM2);                                  //����������������ֵ����ʼ�µļ�����
	led_turn(LED3);

	

	PIT_Flag_Clear(PIT0);
}

