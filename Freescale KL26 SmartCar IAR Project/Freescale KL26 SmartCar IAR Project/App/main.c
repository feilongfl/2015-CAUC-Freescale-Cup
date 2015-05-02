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
/* ȫ�ֱ�����ṹ��                                                     */
/************************************************************************/

/************************************************************************/
/*  �ⲿ���ú���                                                     */
/************************************************************************/
extern void UartHandler();
/************************************************************************/
/*                       ������                                         */
/************************************************************************/
void main()
{
	//////////////////////////////////////////////////////////////////////////
	//                       �ֲ�������ṹ��                               //
	//////////////////////////////////////////////////////////////////////////
	uint8 lostLine = TRUE;
	struct FLAdc_s adcn;
	//////////////////////////////////////////////////////////////////////////
	//                       λ����ʾ                                       //
	//////////////////////////////////////////////////////////////////////////


	/************************************************************************/
	/* ���ж�                                                               */
	/************************************************************************/
	
	set_vector_handler(UART0_VECTORn, UartHandler);   // �����жϷ��������ж���������
	uart_rx_irq_en(UART0);//�����ж�
	//uart_rx_irq_en(BlueToothUartPort);//���������ж�
	FLKeyIrqEnable();
        //wdog_init (1000);//��ʼ�����Ź�
        //wdog_enable ();
	//////////////////////////////////////////////////////////////////////////
	//                       �û�����                                       //
	//////////////////////////////////////////////////////////////////////////
	
	printf("start");
#if 0
	AdcNormalizingInit();//��ʼ����һ������
#else
	LCDPrint(0, 0, "start!");
	AdcInit();
	extern struct FLAdc_s AdcMax;
	uint16 * adcMaxAddress = (uint16*)&AdcMax;
	uint16 adcmaxarr[FLAdcMax] = { 116, 141, 137, 143 };
	for (uint8 loopTemp = 0; loopTemp < FLAdcMax; loopTemp++)
	{
		*(adcMaxAddress + loopTemp) = adcmaxarr[loopTemp];
	}
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
	
#endif
	uint16 spwm = 1500;
	//tpm_pwm_duty(TpmMotor, TpmMotorCh0, 3000);
	enable_irq(PIT_IRQn);								  //ʹ��PIT0�ж�
	//����ѭ��
	while (1)
	{
		adcn = AdcNormalizing();
		SteerTurnDirection_e turn = SteerDirectionSetByAdcOne(&adcn);
		SteerDeviationDegree_e de = SteerDeviationDegreeSetByAdc(&adcn);
		int32 pidatsteer = SteerCtrlUsePid(de);
		NumShow(ABS(de), 0, 0);

		

		for (uint8 adcTemp = FLAdcMax; adcTemp > FLAdcMax / 2; adcTemp--)
		{
			lostLine &= (*((uint16*)&adcn + FLAdcMax - adcTemp) > LostLineAdcMin) ? false : true;//�ж϶���
			lostLine &= (*((uint16*)&adcn + adcTemp - 1) > LostLineAdcMin) ? false : true;
		}

		if (lostLine)
		{
			disable_irq(PIT_IRQn);
			tpm_pwm_duty(TpmMotor, TpmMotorCh0, 0);
		}
		else
		{
			enable_irq(PIT_IRQn);
		}
		

		if (spwm - pidatsteer < 1100 || spwm - pidatsteer > 1900)
		{
			led(LED3, LED_ON);
		}
		else
		{
			spwm -= pidatsteer;
			led(LED3, LED_OFF);
			tpm_pwm_duty(TpmSteer, TpmSteerCh, spwm);
		}
		/*printf("$%d,%d,%d,%d,%d,%d,%d,%d#", (uint8)turn, de,
			adcn.FLAdc0, adcn.FlAdc1, adcn.FLAdc2, adcn.FLAdc3
			, pidatsteer, spwm); 
*/

		DELAY_MS(20);



		


		//tpm_pwm_duty(TpmMotor, TpmMotorCh0, 0);
		//lptmr_time_start_us();                  //��ʼ��ʱ
		//adcn = AdcNormalizing();
		//adcn = AdcNormalizingWithFitter();
		//uint32 t = lptmr_time_get_us();          //ֹͣ��ʱ����ȡ��ʱʱ��
		//DELAY_MS(100);
		//printf("\n%d\n", t);

		// 		printf("$%d,%d,%d,%d,0,0,0,0#",
		// 			adcn.FLAdc0, adcn.FlAdc1, adcn.FLAdc2, adcn.FLAdc3);
		//Hcsr04Read();
		//CoderRead ();
		//led_turn(LED3);

		//LcdShowAllData(); 
		//wdog_feed ();
		//DELAY_MS(5000);
	}






	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Don't leave main////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}


