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

void turn()
{
	switch (key_scan())
	{
	case KEY_L:
		nrf_msg_tx(COM_Ctrl, "+l");
		while (key_check(KEY_L) == KEY_DOWN);
		nrf_msg_tx(COM_Ctrl, "-l");
		break;

	case KEY_R:
		nrf_msg_tx(COM_Ctrl, "+r");
		while (key_check(KEY_R) == KEY_DOWN);
		nrf_msg_tx(COM_Ctrl, "-r");
		break;

	default:
		break;
	}
}

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
	key_init(KEY_MAX);

	while (TRUE)
	{
		switch (key_scan())
		{
		case KEY_U:
			nrf_msg_tx(COM_Ctrl, "+u");
			while (key_check(KEY_U) == KEY_DOWN)
			{
				turn();
			}
			nrf_msg_tx(COM_Ctrl, "-u");
			break;

		case KEY_D:
			nrf_msg_tx(COM_Ctrl, "+b");
			while (key_check(KEY_D) == KEY_DOWN)
			{
				turn();
			}
			nrf_msg_tx(COM_Ctrl, "-b");
			break;

		case KEY_A:
			nrf_msg_tx(COM_Ctrl, "+a");
			while (key_check(KEY_A) == KEY_DOWN);
			nrf_msg_tx(COM_Ctrl, "-a");
			break;

		default:
			break;
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

