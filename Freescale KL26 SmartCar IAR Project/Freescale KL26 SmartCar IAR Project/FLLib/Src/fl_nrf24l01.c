#include "fl_nrf24l01.h"



uint8  nrf_rx_buff[Nrf_DataLen + 2 * Nrf_CommandLen + DATA_PACKET];         //预多
uint8  nrf_tx_buff[Nrf_DataLen + 2 * Nrf_CommandLen + DATA_PACKET];         //预多
const uint32 nrf_com_size[Nrf_CommandMax] = { 0,//checklink
2,//控制
4,//设置
sizeof(struct FreescaleCarState)//状态
										 };

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