#include "fl_nrf24l01.h"



uint8  nrf_rx_buff[Nrf_DataLen + 2 * COM_LEN + DATA_PACKET];         //预多
uint8  nrf_tx_buff[Nrf_DataLen + 2 * COM_LEN + DATA_PACKET];         //预多
const uint32 nrf_com_size[COM_MAX] = { 0,//checklink

										0 };//保留

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

NrfErrorType_e NrfSendMsg(NrfCommand_e * com, uint8 * reBuff)
{

}

NrfErrorType_e NrfReceive()
{
	NrfCommand_e com;
	NrfErrorType_e nrf_result;
	do
	{
		nrf_result = nrf_msg_rx(&com, nrf_rx_buff);
		if (nrf_result == NRF_RESULT_RX_VALID)
		{
			switch (com)
			{
			case Nrf_CheckLink:
				NrfSendMsg(&com, nrf_tx_buff);
				break;
			default:
				break;
			}
		}
	} while (nrf_result != NRF_RESULT_RX_NO);         //接收不到数据 才退出
}
