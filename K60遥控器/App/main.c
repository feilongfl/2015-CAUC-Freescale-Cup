/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外初学论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

void PORTE_IRQHandler();

/*! 
 *  @brief      main函数
 *  @since      v5.0
 *  @note       SPI 驱动 NRF24L01+ 
 */
void main(void)
{
	uint32 i;
	com_e     com;
	nrf_result_e nrf_result;

	while (!nrf_init());
	//配置中断复位函数
	set_vector_handler(PORTE_VECTORn, PORTE_IRQHandler);    			//设置 PORTE 的中断复位函数为 PORTE_VECTORn
	enable_irq(PORTE_IRQn);
	nrf_msg_init();                                                     //无线模块消息初始化

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
 *  @brief      PORTE中断服务函数
 *  @since      v5.0
 */
void PORTE_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    flag = PORTE_ISFR;
    PORTE_ISFR  = ~0;                                   //清中断标志位

    n = 27;
    if(flag & (1 << n))                                 //PTE27触发中断
    {
        nrf_handler();
    }
}

