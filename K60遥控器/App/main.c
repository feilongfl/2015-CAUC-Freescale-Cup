/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ���ѧ��̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

void PORTE_IRQHandler();

/*! 
 *  @brief      main����
 *  @since      v5.0
 *  @note       SPI ���� NRF24L01+ 
 */
void main(void)
{
	uint32 i;
	com_e     com;
	nrf_result_e nrf_result;

	while (!nrf_init());
	//�����жϸ�λ����
	set_vector_handler(PORTE_VECTORn, PORTE_IRQHandler);    			//���� PORTE ���жϸ�λ����Ϊ PORTE_VECTORn
	enable_irq(PORTE_IRQn);
	nrf_msg_init();                                                     //����ģ����Ϣ��ʼ��

	while (TRUE)
	{
		nrf_result = nrf_msg_rx(&com, nrf_rx_buff);
		if (nrf_result == NRF_RESULT_RX_VALID)
		{
			switch (com)
			{
			case COM_Ctrl:

				break;

			default:
				break;
			}
		}
	}
}

/*!
 *  @brief      PORTE�жϷ�����
 *  @since      v5.0
 */
void PORTE_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    flag = PORTE_ISFR;
    PORTE_ISFR  = ~0;                                   //���жϱ�־λ

    n = 27;
    if(flag & (1 << n))                                 //PTE27�����ж�
    {
        nrf_handler();
    }
}

