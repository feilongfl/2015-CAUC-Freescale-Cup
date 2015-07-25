#include "common.h"
#include "fl_cfg.h"
#include "VCAN_NRF24L0.h"
#include "VCAN_NRF24L0_MSG.h"
#include "fl_state.h"

#ifndef _FL_nrf24l01_
#define _FL_nrf24l01_


#define Nrf_DataLen 128
#define Nrf_CommandLen 2

#define NrfInitRetryTime 20//重试次数


NrfErrorType_e NrfInit();//初始化
NrfErrorType_e NrfSendStr(uint8 * str, uint32 len);//发送字符串
NrfErrorType_e NrfSendStrCheck(uint8 * str, uint32 len, uint8 retryTime);//带重试

uint8 NrfRecStrCheck(uint8 * buff, uint8 retryTime);//接收

#endif//_FL_nrf24l01+_
