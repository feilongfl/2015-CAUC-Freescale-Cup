#include "common.h"
#include "MKL_port.h"
#include "MKL_gpio.h"
#include "FL_Key.h"
#include "fl_settingmenu.h"
#include "main.h"


PTXn_e FLKeyPtxn[KeyMax][FLKeyPortNum] =
{
	{ KeyLine1, KeyRank1 }/*Kp*/, { KeyLine1, KeyRank2 }/*���*/, { KeyLine1, KeyRank3 }/*up\+1*/, { KeyLine1, KeyRank4 }/*+10*/,
	{ KeyLine2, KeyRank1 }/*Ki*/, { KeyLine2, KeyRank2 }/*���*/, { KeyLine2, KeyRank3 }/*down\-1*/, { KeyLine2, KeyRank4 }/*-10*/,
	{ KeyLine3, KeyRank1 }/*Kd*/, { KeyLine3, KeyRank2 }/*speed*/, { KeyLine3, KeyRank3 }/*back*/, { KeyLine3, KeyRank4 }/*enter*/,
	{ KeyLine4, KeyRank1 }/*����*/, { KeyLine4, KeyRank2 }/*��һ��*/, { KeyLine4, KeyRank3 }/*reset*/, { KeyLine4, KeyRank4 }/*irq���˵�*/
};

PTXn_e FLKeyPort[KeyPortMax] =
{
	KeyLine1, KeyLine2, KeyLine3, KeyLine4,
	KeyRank1, KeyRank2, KeyRank3, KeyRank4
};

/************************************************************************/
/* ���ư����̷ܽ�����                                                   */
/************************************************************************/
InitRepot_e    FLKeyInit()
{
	//ASSERT();//����Ӧ�ü�һ������

	//�������г�ʼ��Ϊ�ߵ�ƽ,�����ܰ����¼��������йܽŸ���
	//��ʼ��Ϊ�ߵ�ƽ
	for (uint8 keyPort = KeyLineNum; keyPort > 0;keyPort --)
	{
		gpio_init(FLKeyPort[keyPort - 1], GPO, HIGH);
		port_init_NoALT(FLKeyPort[keyPort - 1], PULLUP);
	}

	for (uint8 keyPort = KeyPortMax; keyPort > KeyLineNum; keyPort--)
	{
		gpio_init(FLKeyPort[keyPort - 1], GPI, HIGH);
		port_init_NoALT(FLKeyPort[keyPort - 1], PULLUP);
	}
	return InitAllGreen;
}

/*!
*  @brief      ��ȡkey״̬��������ʱ������
*  @param      KEY_e           KEY���
*  @return     KEY_STATUS_e    KEY״̬��KEY_DOWN��KEY_DOWN��
*  Sample usage:
				if(key_get(KEY_U) ==  KEY_DOWN)
				{
				printf("\n��������")
				}
*/
KEY_STATUS_e FLKeyGet(FL_KEY_e key)
{
	gpio_set(FLKeyPtxn[key][FLKeyLine], LOW);//ʹ�ܰ���������
	DELAY_US(50);//С��ʱ
	if (gpio_get(FLKeyPtxn[key][FLKeyRank]) == KEY_DOWN)//����������������
	{
		gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//���ð���������
		return KEY_DOWN;
	}
	else
	{
		gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//���ð���������
		return KEY_UP;
	}
}


/*!
*  @brief      ���key״̬������ʱ������
*  @param      KEY_e           KEY���
*  @return     KEY_STATUS_e    KEY״̬��KEY_UP��KEY_DOWN��
*  @since      v5.0
*  Sample usage:
if(key_check(KEY_U) ==  KEY_DOWN)
{
printf("\n��������")
}
*/
KEY_STATUS_e FLKeyCheck(FL_KEY_e key)
{
	gpio_set(FLKeyPtxn[key][FLKeyLine], LOW);//ʹ�ܰ���������
	DELAY_US(50);//С��ʱ
	if (gpio_get(FLKeyPtxn[key][FLKeyRank]) == KEY_DOWN)//����������������
	{
		DELAY_MS(10);//����ʱ
		if (gpio_get(FLKeyPtxn[key][FLKeyRank]) == KEY_DOWN)//����������������
		{
			while (gpio_get(FLKeyPtxn[key][FLKeyRank]) == KEY_DOWN);//�ȴ������ͷ�
			gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//���ð���������
			return KEY_DOWN;
		}
		else
		{
			gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//���ð���������
			return KEY_UP;
		}
	}
	else
	{
		gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//���ð���������
		return KEY_UP;
	}
}


/************************************************************************/
/* �������irqָ��                                                      */
/************************************************************************/
void FLKeyIrqEnable()
{
	//ASSERT();//����Ӧ�ü�һ������

	gpio_set(FLKeyPtxn[FLKeyIrq][FLKeyLine], LOW);//ѡ�а���������
	port_init_NoALT(FLKeyPtxn[FLKeyIrq][FLKeyRank], IRQ_FALLING | PULLUP);//���尴�������� �½��� �����ж�,��������

	//KL26ֻ��pta,��ptc��ptd���������жϣ�
	set_vector_handler(PORTC_PORTD_VECTORn, FLIrqHandle);    //����PORTC��PORTD���жϷ�����Ϊ PORTC_PORTD_IRQHandler
    enable_irq (PORTC_PORTD_IRQn);                                      //ʹ��PORTC��PORTD�ж�
}

void FLKeyIrqDisable()
{
	disable_irq(PORTC_PORTD_IRQn);//���ж�
	FLKeyInit();//�����������У����ü���
}

void FLIrqHandle()
{
#if IrqKeyPort == PortC//�����������
	//��ʵ֤��������ôЩ�ǲ��е�
	//PORT_FUNC(IrqKeyPort, IrqKeyPortNum, FLIrqKeyDown);//ִ�������ж�

	//Ҫ��ôд
	uint8  n = IrqKeyPortNum;    //���ź�
	if (PORTC_ISFR & (1 << n))           //PTC9 �����ж�
	{
		PORTC_ISFR = (1 << n);        //д1���жϱ�־λ
		/*  ����Ϊ�û�����  */
		FLKeyIrqDisable();
		if (FLKeyCheck(FLKeyIrq) == KEY_DOWN)//�����������һ�����жϣ���ȥ��
		{
			tpm_pwm_duty(TpmMotor, TpmMotorCh0, 0);
			tpm_pwm_duty(TpmMotor, TpmMotorCh1, 0);
			while (FLKeyCheck(FLKeyIrq) == KEY_DOWN);
			FLIrqKeyDown();
		}
		FLKeyIrqEnable();
		/*  ����Ϊ�û�����  */

	}
#elif IrqKeyPort == PortD
	uint8  n = IrqKeyPortNum;    //���ź�
	n = 9;
	if (PORTD_ISFR & (1 << n))           //PTC9 �����ж�
	{
		PORTD_ISFR = (1 << n);        //д1���жϱ�־λ

		/*  ����Ϊ�û�����  */

		FLIrqKeyDown();

		/*  ����Ϊ�û�����  */
	}
#else//����
#error The Reset Key Port is wrong!!
#endif
	extern void EndLine();
	//ptc14,�ɻɹ�
	n = 16;
	if (PORTC_ISFR & (1 << n))           //PTC18�����ж�
	{
		PORTC_ISFR = (1 << n);        //д1���жϱ�־λ

		/*  ����Ϊ�û�����  */
		EndLine();

		/*  ����Ϊ�û�����  */
	}

	//PTC18��nrf
	extern void nrf_handler();//�鷳�ˣ����ﾹȻ��nrf����һ���ж�
	n = 18;
	if (PORTC_ISFR & (1 << n))           //PTC18�����ж�
	{
		PORTC_ISFR = (1 << n);        //д1���жϱ�־λ
		
		/*  ����Ϊ�û�����  */
		nrf_handler();

		/*  ����Ϊ�û�����  */
	}

	if (FreecaleConfig.Config.CarThis == MyCar2)
	{
		// 	extern void Hcsr04Irq();
		// 	n = 1;
		// 	if (PORTD_ISFR & (1 << n))          
		// 	{
		// 		PORTD_ISFR = (1 << n);        //д1���жϱ�־λ
		// 
		// 		/*  ����Ϊ�û�����  */
		// 		extern void Hcsr04IrqPortIrq();
		// 		Hcsr04IrqPortIrq();
		// 		/*  ����Ϊ�û�����  */
		// 	}

		n = 1;
		if (PORTD_ISFR & (1 << n))           
		{
			PORTD_ISFR = (1 << n);        //д1���жϱ�־λ

			/*  ����Ϊ�û�����  */
			extern void Hcsr04EchoIrq();
			Hcsr04EchoIrq();
			/*  ����Ϊ�û�����  */
		}
	}
}

/************************************************************************/
/* ����                                                                 */
/************************************************************************/

FL_KEY_e KeyScan()//�������а���
{
	while (TRUE)
	{
		for (uint8 keyTemp = 0; keyTemp < FLKeyMax; keyTemp++)
		{
			if (FLKeyCheck((FL_KEY_e)keyTemp) == KEY_DOWN)
			{
				return (FL_KEY_e)keyTemp;//���ڵ����˰���:)
			}
		}
	}
}

FL_KEY_e KeyScanWithoutIrq()//ֻɨ��ǰ������
{
	for (uint8 keyTemp = 0; keyTemp < 3; keyTemp++)
	{
		if (FLKeyCheck((FL_KEY_e)keyTemp) == KEY_DOWN)
		{
			return (FL_KEY_e)keyTemp;//���ڵ����˰���:)
		}
	}
	return FLNoKeyDown;
}


void FLIrqKeyDown()
{
	DisableInterrupts();
	FLKeyInit();//�����������ţ��������а���
	//��ʾ����������ģʽ
	SettingMenuInit();
}

