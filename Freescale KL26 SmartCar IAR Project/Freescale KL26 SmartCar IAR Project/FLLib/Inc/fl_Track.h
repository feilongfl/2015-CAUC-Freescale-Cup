

#ifdef MKL26Z4
#include "MKL_adc.h"
#elif MK60F15
#include "MK60_adc.h"
#elif MK60DZ10
#include "MK60_adc.h"
#endif

#ifndef _FL_TRACK_
#define _FL_TRACK_

uint32 AdcReadAndCaluOnce(ADCn_Ch_e adcn_ch);
void AdcInit();
/************************************************************************/
/* 获取电感电压值                                                       */
/************************************************************************/
void TrackScan();

/************************************************************************/
/* 显示电感电压值                                                       */
/************************************************************************/
void TrackShow();
/************************************************************************/
/* 更新并显示电感电压值                                                 */
/************************************************************************/
void TrackShowAutoRead();
/************************************************************************/
/* 串口回传电感电压值                                                   */
/************************************************************************/
void TrackUartSend();
/************************************************************************/
/* 蓝牙回传电感电压值                                                   */
/************************************************************************/
void TrackBluetoothSend();

#endif//_FL_TRACK_