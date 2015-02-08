#include "common.h"
#include "MKL_TPM.h"
/************************************************************************/
/* 管脚定义和其他常量设置                                               */
/************************************************************************/

#ifndef _FL_CFG_
#define _FL_CFG_
/************************************************************************/
/* 其他常量                                          20150107          */
/************************************************************************/
#define MsgMaxLength		 99				//消息数组成员数

/************************************************************************/
/* tpm 参数                                           20150107          */
/************************************************************************/
#define TpmMotorFreq		(400*1000)		//电机频率
#define TpmSteerFreq		(100)		//舵机频率
#define TmpPwmDutyDefault	 0				//初始化tpm模块为pwm功能时的默认值
#define TpmCoder			TPM2			//脉冲计数
#define TpmCodePrecison		TPM2_PRECISON	//占空比精度
#define TpmMotor			TPM0
#define TpmMotorPrecison	TPM0_PRECISON	//占空比精度
#define TpmSteer			TPM1
#define TpmSteerCh			TPM_CH0			
#define TpmSteerPrecison	TPM1_PRECISON	//占空比精度

/************************************************************************/
/* 蓝牙串口配置                                    20150107             */
/************************************************************************/
#define BlueToothUartPort		UART1		//蓝牙连这一个
#define BlueToothUartBaudRate	115200		//波特率太小影响速度
//根据lptmr计时，9600和115200发送23个0的时间分别为19ms和1ms

/************************************************************************/
/* PIT定时                                               20150107       */
/************************************************************************/
#define CoderPit			PIT0		//编码器pit模块
#define CoderTimeCircle		1000		//定时器0周期单位ms
/************************************************************************/
/* 超声波                                               20150107        */
/************************************************************************/
#define Hcsr04Trig			 PTD2
#define Hcsr04Echo			 PTD1
#define Hcsr04FlagWait		 0xFFFFF
/************************************************************************/
/* Olcd                                                                 */
/************************************************************************/
//网上找的模拟iic可以考虑以后换成硬件iic

#define LCD_SCL PTA17	//D0
#define LCD_SDA	PTA16	//d1  mosi
#define LCD_RST PTA13	//rst
#define LCD_DC  PTA12	//dc
/*
官方说明
The 4-wire serial interface consists of serial clock:
SCLK, serial data:
SDIN, D/C#, CS#. In 4-wire SPI mode,
D0 acts as SCLK,
D1 acts as SDIN.For the unused data pins,
D2 should be left open.
The pins from D3 to D7, E and R/W# (WR#)# can be connected to an external ground.
*/
/*硬件spi
#define LcdSpi SPI0//模块号
#define LcdBaud (12500 * 1000)//波特率
#define LcdPcs SPI0_PCS0//片选
#define LcdDc PTA12//数据或命令选择
#define LcdRst PTA13//复位*/
//////////////////////////////////////////////////////////////////////////
//数据位置
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
/* 按键                                                                 */
/************************************************************************/

#define KeyLine1 PTC0
#define KeyLine2 PTC1
#define KeyLine3 PTC2
#define KeyLine4 PTC3

#define KeyRank1 PTC4
#define KeyRank2 PTC5
#define KeyRank3 PTC6
#define KeyRank4 PTC7
