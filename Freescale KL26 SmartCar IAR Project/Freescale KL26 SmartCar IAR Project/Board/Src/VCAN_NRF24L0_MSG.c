/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       VCAN_NRF24L0_MSG.c
 * @brief      ���ߵ��� ��Ϣ���� ����
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2014-01-04
 */

#include "common.h"

#include "VCAN_camera.h"
#include "VCAN_NRF24L0.h"
#include "VCAN_NRF24L0_MSG.h"
//#include "VCAN_TSL1401.h"


struct FLAdc_s Nrf_Adc;
struct Pid_s Nrf_MPid;
struct Pid_s Nrf_SPid;
struct MotorSpeed_s Nrf_Speed;

uint32 rxbuflen = 0;           //���ڽ��շ����ؽ��յ��������ݡ���������һ�δ��ݽ�ȥ���Ǹ�����С��


const uint32 nrf_com_size[COM_MAX] = { Nrf_AdcLenth,//adc
										Nrf_MpidLenth,//mpid
										Nrf_SpidLenth,//spid
										Nrf_SpeedLenth,//speed
										//Nrf_VarLenth,//����
										Nrf_RetranLenth ,//��ջ���
										Nrf_TestLenth //����
};

uint32 nrf_com_totalsize[COM_MAX];                                                                  // ��ռ�� �� �� �� ռ�ÿռ�

void nrf_msg_init()
{
    uint32 i = COM_MAX;

    while(i--)
    {
        nrf_com_totalsize[i] = (( nrf_com_size[i] + 2 * COM_LEN + DATA_PACKET - 1 ) / DATA_PACKET)  //��ð�����Ŀ
                               *DATA_PACKET;                                                      //�ܹ�ռ�õĿռ�
    }

}


//�������ǰ�����ֽ���������ʶ�𣬺��������Ҫ���������
nrf_result_e nrf_msg_tx(com_e  com, uint8 *sendbuf)
{
    ASSERT(com < COM_MAX);          //����ܳ���������Ŀ

    //������д�����ݻ�����
    sendbuf[0] =  com;
    sendbuf[1] = ~com;
    sendbuf[nrf_com_size[com] + 2 * COM_LEN - 2] = ~com;
    sendbuf[nrf_com_size[com] + 2 * COM_LEN - 1] = com;

    while( !nrf_tx(sendbuf , nrf_com_size[com] + 2 * COM_LEN)); //��������

    return NRF_RESULT_NULL;
}

//��ѯ�Ƿ��н������ݣ������д���rebuf Ϊ�ɹ�ʹ�õĻ�����
//
nrf_result_e nrf_msg_rx(com_e  *com, uint8 *rebuf)
{
    com_e   comtmp;
    uint32  len;
    uint32  tmplen;
    uint32  relen;                              //���յ������ݳ���
    uint8   *buftemp;
    uint32  tmp;
    uint32  totallen ;                          //����Ҫ���հ�����Ŀ(����������)
    uint16  tmpcheck;

RE_LOOP:
    buftemp = rebuf;                            //������ʼ��ַ

    relen = nrf_rx(buftemp, DATA_PACKET);       //���� ��һ����
    if(relen == 0)
    {
        //����� ԤУ�� ʧ�ܣ���ô �϶����Խ��յ����ݣ��������˴�

        //ֻ�� һ��ʼ ���뺯�� ��һ�ν��յ�ʱ�򣬲ų��ֽ���ʧ��

        return NRF_RESULT_RX_NO;                //û���յ�����
    }

    comtmp = (com_e)buftemp[0];
    if(((uint8)comtmp < (uint8)COM_MAX) && (buftemp[1] ==  (uint8)~comtmp) && (comtmp != COM_RETRAN) )
    {
        //У����ȷ,��������ʣ�� ������

        totallen = nrf_com_totalsize[comtmp];   //�ܽ��ղ���

        if(totallen > relen )                   //���ݳ��� ���� �ѽ��ճ���
        {
            //��Ҫ��������
            len = totallen - relen;             //ʣ����յ� ����

            //�ȴ�����FIFO�������У����ȷ�Ž���
            while( !nrf_rx_fifo_check(nrf_com_size[comtmp] + 2 * COM_LEN - relen,&tmpcheck)  );   //�ȴ�����
            if( tmpcheck !=  (uint16)((uint8)~comtmp + (comtmp<<8)))
            {
                goto RE_LOOP;                   //У��ʧ�� �������ղŽ��յ� ��һ�� �� �����½������ݣ�
            }

            tmplen = relen;
            do
            {
                buftemp += tmplen;              //�ƶ�����δ�������ݵĻ�����
                tmplen = nrf_rx(buftemp, len);  //��������
                //relen += tmplen;
                len -= tmplen;
            }
            while(len);
        }

        //У��β�������Ƿ���ȷ
        if(
            (rebuf[nrf_com_size[comtmp] + 2 * COM_LEN - 2] ==   (uint8)~comtmp)
            &&  (rebuf[nrf_com_size[comtmp] + 2 * COM_LEN - 1] ==   (uint8) comtmp)   )
        {
            *com = comtmp;                          //�洢����

            //�� ���� ���ݽ��� ����
            switch(*com)
            {
			case COM_ADC:
				struct FLAdc_s * adc = &Nrf_Adc;
				for (uint8 i = 0; i<sizeof(struct FLAdc_s); i++)
				{
					*((uint8 *)adc + i) = *(rebuf + COM_LEN + i);
				}
				break;

			case COM_Mpid:
				struct Pid_s * mpid = &Nrf_MPid;
				for (uint8 i = 0; i < sizeof(struct Pid_s); i++)
				{
					*((uint8 *)mpid + i) = *(rebuf + COM_LEN + i);
				}
				break;

			case COM_Spid:
				struct Pid_s * spid = &Nrf_SPid;
				for (uint8 i = 0; i < sizeof(struct Pid_s); i++)
				{
					*((uint8 *)spid + i) = *(rebuf + COM_LEN + i);
				}
				break;

			case COM_Speed:
				struct MotorSpeed_s * speed = &Nrf_Speed;
				for (uint8 i = 0; i < sizeof(struct MotorSpeed_s); i++)
				{
					*((uint8 *)spid + i) = *(rebuf + COM_LEN + i);
				}
				break;

			case COM_TEST:
#ifdef DEBUG
				printf("I got Test Command!\n");
#endif // DEBUG
				break;

            default:
                break;
            }

            return NRF_RESULT_RX_VALID;             //������Ч����
        }
    }

    //�н��յ����ݣ�������������Ч
    return NRF_RESULT_RX_NOVALID;
}



