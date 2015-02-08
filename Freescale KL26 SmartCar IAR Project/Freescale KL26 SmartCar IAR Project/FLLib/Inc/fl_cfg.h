#include "common.h"
#include "MKL_TPM.h"
/************************************************************************/
/* �ܽŶ����������������                                               */
/************************************************************************/

#ifndef _FL_CFG_
#define _FL_CFG_
/************************************************************************/
/* ��������                                          20150107          */
/************************************************************************/
#define MsgMaxLength		 99				//��Ϣ�����Ա��

/************************************************************************/
/* tpm ����                                           20150107          */
/************************************************************************/
#define TpmMotorFreq		(400*1000)		//���Ƶ��
#define TpmSteerFreq		(100)		//���Ƶ��
#define TmpPwmDutyDefault	 0				//��ʼ��tpmģ��Ϊpwm����ʱ��Ĭ��ֵ
#define TpmCoder			TPM2			//�������
#define TpmCodePrecison		TPM2_PRECISON	//ռ�ձȾ���
#define TpmMotor			TPM0
#define TpmMotorPrecison	TPM0_PRECISON	//ռ�ձȾ���
#define TpmSteer			TPM1
#define TpmSteerCh			TPM_CH0			
#define TpmSteerPrecison	TPM1_PRECISON	//ռ�ձȾ���

/************************************************************************/
/* ������������                                    20150107             */
/************************************************************************/
#define BlueToothUartPort		UART1		//��������һ��
#define BlueToothUartBaudRate	115200		//������̫СӰ���ٶ�
//����lptmr��ʱ��9600��115200����23��0��ʱ��ֱ�Ϊ19ms��1ms

/************************************************************************/
/* PIT��ʱ                                               20150107       */
/************************************************************************/
#define CoderPit			PIT0		//������pitģ��
#define CoderTimeCircle		1000		//��ʱ��0���ڵ�λms
/************************************************************************/
/* ������                                               20150107        */
/************************************************************************/
#define Hcsr04Trig			 PTD2
#define Hcsr04Echo			 PTD1
#define Hcsr04FlagWait		 0xFFFFF
/************************************************************************/
/* Olcd                                                                 */
/************************************************************************/
//�����ҵ�ģ��iic���Կ����Ժ󻻳�Ӳ��iic

#define LCD_SCL PTA17	//D0
#define LCD_SDA	PTA16	//d1  mosi
#define LCD_RST PTA13	//rst
#define LCD_DC  PTA12	//dc
/*
�ٷ�˵��
The 4-wire serial interface consists of serial clock:
SCLK, serial data:
SDIN, D/C#, CS#. In 4-wire SPI mode,
D0 acts as SCLK,
D1 acts as SDIN.For the unused data pins,
D2 should be left open.
The pins from D3 to D7, E and R/W# (WR#)# can be connected to an external ground.
*/
/*Ӳ��spi
#define LcdSpi SPI0//ģ���
#define LcdBaud (12500 * 1000)//������
#define LcdPcs SPI0_PCS0//Ƭѡ
#define LcdDc PTA12//���ݻ�����ѡ��
#define LcdRst PTA13//��λ*/
//////////////////////////////////////////////////////////////////////////
//����λ��
//////////////////////////////////////////////////////////////////////////
#define MoterExpectX 32
#define MoterExpectY 6
#define MoterActuallyX 64
#define MoterActuallyY 6

#define TrackingAVoltageX 0
#define TrackingAVoltageY 0
#define TrackingBVoltageX 32
#define TrackingBVoltageY 0
#define TrackingCVoltageX 64
#define TrackingCVoltageY 0
#define TrackingDVoltageX 96
#define TrackingDVoltageY 0
#define TrackingEVoltageX 0
#define TrackingEVoltageY 2

#define DistanceX 96
#define DistanceY 2

/************************************************************************/
/* adc*/
/************************************************************************/
#define FlAdc0 ADC0_DM0
#define FlAdc1 ADC0_DM1
#define FlAdc2 ADC0_DM2
#define FlAdc3 ADC0_DM3
#define FlAdc4 ADC0_DP0

#define FlAdcBit ADC_8bit
#define calcualteAdc(num) ((num * 3300) / 256)


/************************************************************************/
/* sd card spi                                                           */
/************************************************************************/

#define SdSpi SPI1
#define SdSpiPcs SPI_PCS0
#define SdBand (100 * 1000)
#endif //_FL_CFG_


/************************************************************************/
/* ����                                                                 */
/************************************************************************/

#define KeyLine1 PTC0
#define KeyLine2 PTC1
#define KeyLine3 PTC2
#define KeyLine4 PTC3

#define KeyRank1 PTC4
#define KeyRank2 PTC5
#define KeyRank3 PTC6
#define KeyRank4 PTC7
