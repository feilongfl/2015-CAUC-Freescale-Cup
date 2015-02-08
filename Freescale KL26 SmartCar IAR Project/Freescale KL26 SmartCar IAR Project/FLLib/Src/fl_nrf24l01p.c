
#include "common.h"
#include "vcan_nrf24l0.h"
#include "fl_nrf24l01p.h"


uint8 buff[DATA_PACKET];//��ʱ����
uint8 data[DATA_PACKET];//��������
uint8 relen;

/************************************************************************/
/* ��������                                    20150107                 */
/************************************************************************/
void NrfSend(uint8 * str)
{
	FuncLocalShow("Hcsr04Init");
	sprintf((char *)buff, "%s", str);         //��str��i�ϲ���һ���ַ�����buff��ٽ��з���
	nrf_tx(buff, DATA_PACKET);                   //����һ�����ݰ���buff����Ϊ32�ֽڣ�
	//�ȴ����͹����У��˴����Լ��봦������
	while (nrf_tx_state() == NRF_TXING);         //�ȴ��������
	if (NRF_TX_OK == nrf_tx_state())
	{
		MessageShow("\n���ͳɹ�");
	}
	else
	{
		MessageShow("\n����ʧ��");
	}
}

/************************************************************************/
/*  ��ѯ����                                     20150107               */
/************************************************************************/
void NrfRev()
{
	FuncLocalShow("Hcsr04Init");
	relen = nrf_rx(buff, DATA_PACKET);               //�ȴ�����һ�����ݰ������ݴ洢��buff��
	if (relen != 0)
	{
		sprintf((char*)data, "%s", buff);
	}
	else
	{
		data[0] = 0;//û�յ����ݡ�
	}
}



/*!
*  @brief      PORTC��D�жϷ�����
*  @since      v5.0
*/
void PORTC_PORTD_IRQHandler()
{
	FuncLocalShow("Hcsr04Init");
	uint8  n = 0;    //���ź�
	//PTC18
	n = 18;
	if (PORTC_ISFR & (1 << n))           //PTC18�����ж�
	{
		PORTC_ISFR = (1 << n);        //д1���жϱ�־λ
		/*  ����Ϊ�û�����  */
		nrf_handler();
		/*  ����Ϊ�û�����  */
	}
}


/************************************************************************/
/* ��ʼ��nrf24L01+                                                      */
/************************************************************************/
void NrfInit()
{
	FuncLocalShow("NrfInit");
	while (!nrf_init())                  //��ʼ��NRF24L01+ ,�ȴ���ʼ���ɹ�Ϊֹ
	{
		printf("\n  nrf24L01+ connect failed\n");
	}
	set_vector_handler(PORTC_PORTD_VECTORn, PORTC_PORTD_IRQHandler);    			//���� PORTE ���жϷ�����Ϊ PORTE_VECTORn
	enable_irq(PORTC_PORTD_IRQn);
	MessageShow("NRF is connected");
	
}

