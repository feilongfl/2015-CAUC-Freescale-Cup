
#include "common.h"
#include "fl_track.h"
#include "fl_olcd.h"

uint32 TrackA = 0;
uint32 TrackB = 0;
uint32 TrackC = 0;
uint32 TrackD = 0;
uint32 TrackE = 0;

char TrackStr[] = "\0";

void AdcInit()
{
	adc_init(ADC0_DM0);
	adc_init(ADC0_DM1);
	adc_init(ADC0_DM2);
	adc_init(ADC0_DM3);
	adc_init(ADC0_DP0);
}
/*
uint32 calcualteAdc(uint16 num)
{
	return ((num * 3300) / 256);
}
*/
uint32 AdcReadAndCaluOnce(ADCn_Ch_e adcn_ch)
{
	return calcualteAdc(adc_once(adcn_ch, FlAdcBit));
}

void TrackScan()
{
	TrackA = AdcReadAndCaluOnce(FlAdc0);
	TrackB = AdcReadAndCaluOnce(FlAdc1);
	TrackC = AdcReadAndCaluOnce(FlAdc2);
	TrackD = AdcReadAndCaluOnce(FlAdc3);
	TrackE = AdcReadAndCaluOnce(FlAdc4);
}


void TrackShow()
{
	NumShow(TrackA, TrackingAVoltageX, TrackingAVoltageY);
	NumShow(TrackB, TrackingBVoltageX, TrackingBVoltageY);
	NumShow(TrackC, TrackingCVoltageX, TrackingCVoltageY);
	NumShow(TrackD, TrackingDVoltageX, TrackingDVoltageY);
	NumShow(TrackE, TrackingEVoltageX, TrackingEVoltageY);
}

void TrackShowAutoRead()
{
	TrackScan();
	TrackShow();
}

void TrackUartSend()
{

}

void TrackBluetoothSend()
{

}
