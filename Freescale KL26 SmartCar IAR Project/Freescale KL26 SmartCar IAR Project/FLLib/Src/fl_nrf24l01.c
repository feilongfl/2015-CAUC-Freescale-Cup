#include "fl_nrf24l01.h"



uint8  nrf_rx_buff[Nrf_DataLen + 2 * COM_LEN + DATA_PACKET];         //Ԥ��
uint8  nrf_tx_buff[Nrf_DataLen + 2 * COM_LEN + DATA_PACKET];         //Ԥ��
const uint32 nrf_com_size[COM_MAX] = { 0,//checklink

										0 };//����

NrfErrorType_e NrfInit()
{
	uint8 i = NrfInitRetryTime;
	while (!nrf_init())                  //��ʼ��NRF24L01+ ,�ȴ���ʼ���ɹ�Ϊֹ
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
	if (nrf_tx(str, DATA_PACKET) == 1)         //����һ�����ݰ���buff����Ϊ32�ֽڣ�
	{
		//�ȴ����͹����У��˴����Լ��봦������

		while (nrf_tx_state() == NRF_TXING);         //�ȴ��������

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
	} while (nrf_result != NRF_RESULT_RX_NO);         //���ղ������� ���˳�
}
