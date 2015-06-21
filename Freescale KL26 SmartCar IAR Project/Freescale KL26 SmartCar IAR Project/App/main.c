/*!
*
* @file       main.c
* @brief      ��˼����������
* @author     ����
* @version    v0.1
* @date       2015-1-7
*/
/************************************************************************/
/* �ļ�����                                                             */
/************************************************************************/
#include "main.h"

/************************************************************************/
/*                                 ���ܿ���                             */
/************************************************************************/
#define UseAdcNormalizingInit		DoNotUseIt//������һ��ʹ��
#define UseEndLine					DoNotUseIt
#define UsePowerOnDelay				UseIt
#define UseEeprom					DoNotUseIt
#define UseLostRoadStop				UseIt

#define SpeedForTest				500

/************************************************************************/
/* ȫ�ֱ�����ṹ��                                                     */
/************************************************************************/
uint8 lostRoad = 0;
/************************************************************************/
/*  �ⲿ���ú���                                                     */
/************************************************************************/
extern void UartHandler();


//////////////////////////////////////////////////////////////////////////
//���ģ�������㷨
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*���Ա���ָ��*/
//���ƫ��仯��Χmax = 63
//����ǰƫ�����ֵmax=44
//
//ģ��������ƫ�Χ-6~6
#define SteerOffSetSum 13
//�ο�������������ǰ�ֵ�˼�룬�ݶ�7��
#define SteerGears 7
//ƫ�����Ա���ֵ��
//���ͻ����������������ֳ�8
char SteerCRI[SteerGears][SteerOffSetSum] = {
	8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 4, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 4, 8, 4, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 4, 8, 4, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 4, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8,
};
//���pwm����
int16 SteerPwmArr[SteerGears] = {
#if 1
	1000, 1200, 1400, 1500, 1600, 1800, 2000
#elif 0
	- 550, -300, -100, 0, 100, 300, 500
#else
	1000, 1167, 1333, 1500, 1667, 1833, 2000
#endif
};
/************************************************************************/
//offset:ƫ��
void VagueCtrl(int16 offset)
{
	offset = RANGE(offset, 59, -59) + 60;//�޷�+����ԭ��
	
	offset /= 10;//ƫ��ģ����
	uint16 sum = 0;
	uint16 pwm = 0;

	if (!RANGEQurr(offset, 8, 5))//��ֱ
	{
		for (uint8 i = 0; i < SteerGears;i++)//���ĸ
		{
			sum += SteerCRI[i][offset];
			sum += SteerCRI[i][offset + 1];
		}

		for (uint8 i = 0; i < SteerGears; i++)//��pwm
		{
			pwm += SteerPwmArr[i] * (SteerCRI[i][offset] + SteerCRI[i][offset + 1]) / sum;
		}
	}
	else//���ֱͦ��
	{
		pwm = SteerCenterDuty;
	}
	tpm_pwm_duty(TpmSteer, TpmSteerCh, pwm);
}
//////////////////////////////////////////////////////////////////////////

void SteerCtrl()
{
	struct FLAdc_s adcn;
	FLAdcLostLine_e IsLostLine = LostLine;

	adcn = AdcNormalizing();//��ȡ��һ�����ֵ
	SteerTurnDirection_e turn = SteerDirectionSetByAdcOne(&adcn, &IsLostLine);
	SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);
	//int32 pidatsteer = SteerCtrlUsePid(de);
	NumShow(ABS(de), 0, 0);

	if (IsLostLine == LostLine)//����
	{
		led(LED0, LED_ON);
#if UseLostRoadStop
		Speed.Expect = (lostRoad > 10) ? 0 : SpeedForTest;
		lostRoad = (lostRoad > 10) ? 255 : lostRoad++;
#endif//UseLostRoadStop
		switch (turn)
		{
		case SteerDirectionLeft:
			tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty + 500);
			break;

		case SteerDirectionRight:
			tpm_pwm_duty(TpmSteer, TpmSteerCh, SteerCenterDuty - 500);
			break;

		case SteerDirectionCenter:
			led(LED2, LED_ON);
			//ֱ��
			break;

		default:
			break;
		}
	}
	else//OnLine
	{
#if UseLostRoadStop
		lostRoad = 0;
		Speed.Expect = SpeedForTest;
#endif//UseLostRoadStop
		VagueCtrl(de);
		led(LED0, LED_OFF);

		
	}
}



/************************************************************************/
/*                       ������                                         */
/************************************************************************/
void main()
{
	//////////////////////////////////////////////////////////////////////////
	//                       �ֲ�������ṹ��                               //
	//////////////////////////////////////////////////////////////////////////
	ConfigInit();
	
	//////////////////////////////////////////////////////////////////////////
	//                       λ����ʾ                                       //
	//////////////////////////////////////////////////////////////////////////
	/************************************************************************/
	/* ���ж�                                                               */
	/************************************************************************/
	
	set_vector_handler(UART0_VECTORn, UartHandler);   // �����жϷ��������ж���������
	uart_rx_irq_en(UART0);//�����ж�
	FLKeyIrqEnable();
        //wdog_init (1000);//��ʼ�����Ź�
        //wdog_enable ();
	//////////////////////////////////////////////////////////////////////////
	//                       �û�����                                       //
	//////////////////////////////////////////////////////////////////////////
#if UseEndLine
	switch (FreecaleConfig.Config.CarState)
	{
	case CarStandby:
#endif//UseEndLine
		printf("start");
#if UseAdcNormalizingInit
		AdcNormalizingInit();//��ʼ����һ������
#else//UseAdcNormalizingInit
		LCDPrint(0, 0, "start!");
		AdcInit();
		uint8 exitfunc = false;

		while (!exitfunc)
		{
			switch (KeyScanWithoutIrq())//�������
			{
			case FLKeyAdcNorExit:
				exitfunc = TRUE;//�˳�
				break;

			default:
				break;
			}
		}
#endif//UseAdcNormalizingInit
#if UsePowerOnDelay
		DELAY_MS(2000);
#endif//UsePowerOnDelay

#if UseEndLine
		break;

	case CarRunning:
		break;

	case CarFinish:
		LCDPrint(0, 0, "Finish!");
		break;

	default:
		break;
	}
#endif//UseEndLine

	
	

	uint16 spwm = SteerCenterDuty;
	Speed.Expect = SpeedForTest;
	enable_irq(PIT_IRQn);								  //ʹ��PIT0�ж�
	//����ѭ��
	while (1)
	{
		SteerCtrl();

#if 1
		
#else

		
		NumShow16(Speed.Expect, LcdLocal1, LcdLine1);
		NumShow16(Speed.Acturally, LcdLocal1, LcdLine2);
		
		NumShow(MotorPid.P, LcdLocal1, LcdLine3);
		NumShow(MotorPid.I, LcdLocal2, LcdLine3);
		NumShow(MotorPid.D, LcdLocal3, LcdLine3);
		
#endif
		DELAY_MS(100);
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Don't leave main////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


