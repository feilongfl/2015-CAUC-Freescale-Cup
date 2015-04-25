#include "fl_nrf24l01.h"



uint8  nrf_rx_buff[Nrf_DataLen + 2 * Nrf_CommandLen + DATA_PACKET];         //Ԥ��
uint8  nrf_tx_buff[Nrf_DataLen + 2 * Nrf_CommandLen + DATA_PACKET];         //Ԥ��
const uint32 nrf_com_size[Nrf_CommandMax] = { 0,//checklink
2,//����
4,//����
sizeof(struct FreescaleCarState)//״̬
										 };

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
	nrf_msg_init();//��ʼ����Ϣ
	return Nrf_AllGreen;
}