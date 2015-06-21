
#include "common.h"
#include "fl_irq.h"

static uint8 uartCmdLocal = 0;
static char uartCmdBuff[100];
UartCmdAvailable uartCmdAvailable = NotAvailable;

static uint16 e10(int16 x)
{
  uint32 renum = 1;
  while(x--)
  {
    renum *= 10;
  }
  return renum;
}

static uint16 getNumFromCharArr(char * str, uint8 len)
{
	uint16 cData = 0;
	for (uint8 i = 1; i < len; i++)
	{
		cData += (str[i] - 48) * e10((len - i) - 1);
	}
}

static void pidCmdAnalyze(char * cmd, uint8 cmdLen,SettingErr_e (*func)(Pid_e pidType,uint16 exData))
{
	uint16 cData = getNumFromCharArr(cmd, cmdLen);
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
	//局部变量，存储命令位置
	uint8 cmdReadLocal = 1;
	//断言：命令前缀
	ASSERT(cmd[0] == '$');

	//判断
	switch (cmd[1])
	{
	case 'S':
		pidCmdAnalyze(cmd + 2, cmdLen - 2, SteerPidSet);
		break;

	case 'M':
		pidCmdAnalyze(cmd + 2, cmdLen - 2, MotorPidSet);
		break;

	case 'C'://车速
		Speed.Expect = RANGE(getNumFromCharArr(cmd + 1, cmdLen - 1), MotorSpeedMax,0);
		break;

	case 'T'://停
		Speed.Expect = 0;
		break;

	default:
		printf("error!\n");
		break;
	}
}

/************************************************************************/
/*       串口中断处理函数                                               */
/************************************************************************/
void UartHandler()
{
	////////////////串口//////////////////////////////////////////////////////////
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
				// TODO: 命令处理
				uartCmdAnalyze(uartCmdBuff, uartCmdLocal);
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
	
    MotorCtrl();
	extern uint32 mpwm;
	//printf("$%d,1000,%d,0,0,0,0,0#", Speed.Acturally, mpwm);
	tpm_pulse_clean(TPM2);                                  //清空脉冲计数器计算值（开始新的计数）
	led_turn(LED3);

	

	PIT_Flag_Clear(PIT0);
}

