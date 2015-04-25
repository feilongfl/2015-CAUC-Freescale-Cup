#include "fl_nrf24l01.h"

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

