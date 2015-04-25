#include "common.h"
#include "fl_cfg.h"
#include "VCAN_NRF24L0.h"
//#include "VCAN_NRF24L0_MSG.h"
#include "fl_state.h"

#ifndef _FL_nrf24l01_
#define _FL_nrf24l01_

typedef enum 
{
	Nrf_AT_Car_1,
	Nrf_AT_Car_2,

	Nrf_AT_RC
}NrfLocal_e;//ö������ģ��λ��

#define Nrf_This Nrf_AT_Car_1//���嵱ǰģ��λ��
#define Nrf_DataLen 128
#define Nrf_CommandLen 2

typedef enum 
{
	Nrf_AllGreen,
	Nrf_NotOnLine,
	Nrf_SendFail,
	Nrf_ResultRxValid,
	Nrf_ResultRxNo,

	Nrf_Others
}NrfErrorType_e;

typedef enum 
{
	Nrf_CheckLink,//����checklink�ظ�checklink
	Nrf_Ctrl,//ң��
	Nrf_Set,//����
	Nrf_State,//״̬

	Nrf_CommandMax
}NrfCommand_e;

#define NrfInitRetryTime 20//���Դ���


NrfErrorType_e NrfInit();//��ʼ��
NrfErrorType_e NrfSendStr(char * str, uint32 len);//�����ַ���

#endif//_FL_nrf24l01+_
