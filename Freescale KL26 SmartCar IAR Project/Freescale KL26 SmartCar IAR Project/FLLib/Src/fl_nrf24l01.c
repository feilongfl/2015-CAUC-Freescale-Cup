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
	nrf_msg_init();//初始化消息
	return Nrf_AllGreen;
}

NrfErrorType_e NrfSendStr(uint8 * str,uint32 len)
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

NrfErrorType_e NrfSendStrCheck(uint8 * str, uint32 len,uint8 retryTime)
{
	NrfErrorType_e msg = Nrf_Others;
	while (retryTime--)
	{
		msg = NrfSendStr(str, len);
		if (msg == Nrf_AllGreen)
		{
			return msg;
		}
	}
	return msg;
}


uint8 NrfRecStrCheck(uint8 * str, uint8 retryTime)
{
	uint8 relen = 0;
	while (retryTime--)
	{
		relen = nrf_rx(str, DATA_PACKET);
		if (relen != 0)
		{
			return relen;
		}
	}
	return relen;
}
