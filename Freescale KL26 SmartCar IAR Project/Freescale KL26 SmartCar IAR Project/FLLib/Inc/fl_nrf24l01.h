#include "common.h"
#include "fl_cfg.h"
#include "VCAN_NRF24L0.h"
#include "VCAN_NRF24L0_MSG.h"
#include "fl_state.h"

#ifndef _FL_nrf24l01_
#define _FL_nrf24l01_

typedef enum 
{
	Nrf_AT_Car_1,
	Nrf_AT_Car_2,

	Nrf_AT_RC
}NrfLocal_e;//枚举无线模块位置

#define Nrf_This Nrf_AT_Car_1//定义当前模块位置
#define Nrf_DataLen 128

typedef enum 
{
	Nrf_AllGreen,
	Nrf_NotOnLine,
	Nrf_SendFail,

	Nrf_Others
}NrfErrorType_e;

typedef enum 
{
	Nrf_CheckLink,//发送checklink回复checklink
	

	Nfr_CommandMax
}NrfCommand_e;

#define NrfInitRetryTime 20//重试次数


NrfErrorType_e NrfInit();//初始化
NrfErrorType_e NrfSendStr(char * str, uint32 len);//发送字符串

#endif//_FL_nrf24l01+_
