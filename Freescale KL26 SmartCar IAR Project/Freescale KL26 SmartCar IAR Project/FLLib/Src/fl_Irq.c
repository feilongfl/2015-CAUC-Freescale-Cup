
#include "common.h"
#include "fl_irq.h"


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
	
	if (num == 0)
	{
	}
	else if (num == 1)
	{
		switch (str[0])
		{
		case 'S'://����
			break;

		case 'U'://ǰ��
			break;

		case 'D'://����
			break;

		default:
			break;
		}
	}
	else if (num == 2)
	{
	}
	else if (num == 3 || num == 4)
	{
		if (num == 3)
		{
			pidtemp = str[2] - 48;
		}
		else
		{
			pidtemp = (str[2] - 48) * 10 + (str[3] - 48);
		}
		switch (str[0])
		{
		case 'M'://���
			switch (str[1])
			{
			case 'P':
				MotorPidSetP(pidtemp);
				break;

			case 'I':
				MotorPidSetP(pidtemp);
				break;

			case 'D':
				MotorPidSetP(pidtemp);
				break;

			case 'S':
				MotorSpeedSet(pidtemp);
				break;

			default:
				break;
			}
			break;
			
		case 'S'://���
			switch (str[1])
			{
			case 'P':
				SteerPidSet(Kp, pidtemp);
				break;

			case 'I':
				SteerPidSet(Ki, pidtemp);
				break;

			case 'D':
				SteerPidSet(Kd, pidtemp);
				break;

			default:
				break;
			}
			break;
			break;

		default:
			break;
		}
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
	printf("$%d,1000,%d,0,0,0,0,0#", Speed.Acturally, mpwm);
	tpm_pulse_clean(TPM2);                                  //����������������ֵ����ʼ�µļ�����
	led_turn(LED3);

	

	PIT_Flag_Clear(PIT0);
}

