/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��KL26 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.2
 * @date       2014-10-26
 */

#include "common.h"
#include "include.h"

uint8  nrf_rx_buff[TSL1401_MAX*TSL1401_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��
uint8  nrf_tx_buff[TSL1401_MAX*TSL1401_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��

//��������
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT_IRQHandler();
void PORTC_PORTD_IRQHandler();

uint8  var1 = 20, var2;
uint16 var3, var4;
uint32 var5, var6;


/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� ���ߵ��� ����ʵ��
 */
void  main(void)
{
    uint32 i;
    com_e     com;
    nrf_result_e nrf_result;


    /************************ LCD Һ���� ��ʼ��  ***********************/
    LCD_init();

    /************************ ����ģ�� NRF ��ʼ��  ***********************/
    while(!nrf_init());
    //�����жϷ�����
    set_vector_handler(PORTC_PORTD_VECTORn ,PORTC_PORTD_IRQHandler);                //���� PORTE ���жϷ�����Ϊ PORTE_VECTORn
    enable_irq(PORTC_PORTD_IRQn);
    nrf_msg_init();                                                     //����ģ����Ϣ��ʼ��

    //����ͷģ�飬��Ҫ ���� ������� ���԰�ģ�飬����������� ����ͼ��ʧ�ܶ�������������
    i = 20;
    while(i--)
    {
        nrf_msg_tx(COM_RETRAN,nrf_tx_buff);                              //���Ͷ�� �� �����ȥ��������� ���ն˵Ļ�������
    }

    /*********************** ������Ϣ ��ʼ��  ***********************/
    key_event_init();                                                   //������Ϣ��ʼ��
    pit_init_ms(PIT0,10);                                               //pit ��ʱ�ж�(���ڰ�����ʱɨ��)
    set_vector_handler(PIT_VECTORn ,PIT_IRQHandler);                  //���� PIT0 ���жϷ�����Ϊ PIT0_IRQHandler
    enable_irq(PIT_IRQn);


    while(1)
    {
        /************************ ���߽�������  ***********************/
        do
        {
            nrf_result = nrf_msg_rx(&com, nrf_rx_buff);
            if(nrf_result == NRF_RESULT_RX_VALID)
            {
                switch(com)
                {

                    case COM_VAR:

                        break;
                    default:
                        break;
                }
            }
        }while(nrf_result != NRF_RESULT_RX_NO);         //���ղ������� ���˳�

        /*********************** ������Ϣ ����  ***********************/
        deal_key_event();               //  �˺���Ϊ ��鰴���������ݰ����¼����޸� ������ֵ

        //�������� ͨ������ �ı������ֵ������� �Լ��������޸ı�����ֵ�������ͳ�ȥ���ɲο��������ӣ�
        //ɽ�����ߵ�������ν��ղ���ʾ���ٶ������Ķ�̬���ݣ�������ָ�������� - ���ܳ������� - ɽ����̳ http://vcan123.com/forum.php?mod=viewthread&tid=4029&ctid=1

    }
}


/*!
 *  @brief      PORTC��D�жϷ�����
 *  @since      v5.0
 */
void PORTC_PORTD_IRQHandler()
{
    uint8  n = 0;    //���ź�

    //PTC18
    n = 18;
    if(PORTC_ISFR & (1 << n))           //PTA6�����ж�
    {
        PORTC_ISFR  = (1 << n);        //д1���жϱ�־λ

        /*  ����Ϊ�û�����  */
        nrf_handler();

        /*  ����Ϊ�û�����  */
    }
}


/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 */
void PIT_IRQHandler()
{
    if(PIT_TFLG(PIT0) == 1 )        //�ж��Ƿ� PIT0 �����ж�
    {
        key_IRQHandler();

        PIT_Flag_Clear(PIT0);
    }
}