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



uint32 CarDistance = 0;


#if UseMpu6050ChangeSpeed
Mpu6050Data mpu6050Data;
#endif

/************************************************************************/
/* ȫ�ֱ�����ṹ��                                                     */
/************************************************************************/
uint8 lostRoad = 0;
/************************************************************************/
/*  �ⲿ���ú���                                                     */
/************************************************************************/
extern void UartHandler();



void SteerCtrl()
{
	struct FLAdc_s adcn;
	FLAdcLostLine_e IsLostLine = LostLine;

	adcn = AdcNormalizing();//��ȡ��һ�����ֵ
	SteerTurnDirection_e turn = SteerDirectionSetByAdcOne(&adcn, &IsLostLine);
	SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);

	uint8 time = 0;
	uint8 turnTemp = 0;
	//int32 pidatsteer = SteerCtrlUsePid(de);
	NumShow(ABS(de), 0, 0);

	if (IsLostLine == LostLine)//����
	{
		led(LED0, LED_ON);
#if UseLostRoadStop
		Speed.Expect = (lostRoad > 10) ? 0 : SpeedForTest;
		lostRoad = (lostRoad > 10) ? 255 : lostRoad+1;

#define SteerLostLinetimeMax 10//ֱ������жϴ���
		if (ABS(adcn.AdcVertical.Adc0 - adcn.AdcVertical.Adc1) > 80)//ֱ������ж���С��ֵ
		{
			turnTemp += ((adcn.AdcVertical.Adc0 > adcn.AdcVertical.Adc1) ? SteerDirectionLeft : SteerDirectionRight) - 1;//�ۼӷ�����ʱ����
			if (time++ > SteerLostLinetimeMax)//�������ж�
			{
				if (RANGEQurr(turnTemp, SteerLostLinetimeMax / 3,  -SteerLostLinetimeMax / 3))//�м�
				{
					turn = SteerDirectionCenter;
				}
				else if (turnTemp > 0)
				{
					turn = SteerDirectionRight;
				}
				else
				{
					turn = SteerDirectionLeft;
				}
				time = 0;
			}
			else//û���ߣ������־
			{
				time = 0;
			}
		}
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
		SteerVagueCtrl(de);
		led(LED0, LED_OFF);

		
	}
}

/************************************************************************/
/* ����                                                               */
/************************************************************************/
void SpeedCtrl()
{
//////////////////////////////////////////////////////////////////////////
/*  �������                                      */
	Speed.Expect = SpeedForTest;
#if UseDistanceChangeSpeed
	#warning please change these num
	if (CarDistance < 100)//only for test,don't forget change this num
	{
#if Car == Car1
		Speed.Expect += 100;//num is for test,car1
#elif Car == Car2
		Speed.Expect -= 100;//num is for test,car2
#endif
	}
	else if (CarDistance > 200)//num is for test
	{
#if Car == Car1
		Speed.Expect -= 100;//num is for test,car1
#elif Car == Car2
		Speed.Expect += 100;//num is for test,car2
#endif
	}
	else
	{
		//Speed.Expect = SpeedForTest;
	}

#endif //UseDistanceChangeSpeed

/*mpu6050 �µ�����*/
#if UseMpu6050ChangeSpeed
	mpu6050Data = Mpu6050Read();
	#warning please test these line
	if (mpu6050Data.accel.z > 10)
	{
		Speed.Expect += 100;
	}
	else if (mpu6050Data.accel.z < 10)
	{
		Speed.Expect -= 100;
	}
	else
	{

	}
#endif //UseMpu6050ChangeSpeed
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

#if Car == Car2
	Hcsr04Init();
#endif //car
	
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


		//////////////////////////////////////////////////////////////////////////
		//�յ���
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
		//////////////////////////////////////////////////////////////////////////
		//�������
		SteerCtrl();

#if 1
		
#else
		///lcd show
		
		NumShow16(Speed.Expect, LcdLocal1, LcdLine1);
		NumShow16(Speed.Acturally, LcdLocal1, LcdLine2);
		
		NumShow(MotorPid.P, LcdLocal1, LcdLine3);
		NumShow(MotorPid.I, LcdLocal2, LcdLine3);
		NumShow(MotorPid.D, LcdLocal3, LcdLine3);
		
#endif


		SpeedCtrl();


		//////////////////////////////////////////////////////////////////////////
		//�ӳ٣���������
#define mainDelayTime 2//2 * 20ms
#if Car == Car1
		DELAY_MS(mainDelayTime * 20);
#elif Car == Car2
		static uint8 carDelayFlag = 0;//static values
		if (carDelayFlag++ < mainDelayTime - 1)
		{
			Hcsr04Wait();
			carDelayFlag = 0;
		}
		else
		{
			CarDistance = Hcsr04Read();
			NrfSendStr("$%d#", CarDistance);
		}
#else
#error your car select error
#endif//Car Switch 
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Don't leave main////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


