#include "fl_nrf24l01.h"

NrfErrorType_e NrfInit()
{
	uint8 i = NrfInitRetryTime;
	while (!nrf_init())                  //初始化NRF24L01+ ,等待初始化成功为止
	{
		if (i-- == 0)
		{
			ASSERT(true);
			return Nrf_NotOnLine;
		}
	}
	return Nrf_AllGreen;
}

NrfErrorType_e NrfSendStr(char * str,uint32 len)
{
	if (nrf_tx(str, DATA_PACKET) == 1)         //发送一个数据包：buff（包为32字节）
	{
		//等待发送过程中，此处可以加入处理任务

		while (nrf_tx_state() == NRF_TXING);         //等待发送完成

		if (NRF_TX_OK == nrf_tx_state())
		{
			return Nrf_AllGreen;
		}
		else
		{
			return Nrf_SendFail;
		}
	}
	else
	{
		return Nrf_SendFail;
	}
}

