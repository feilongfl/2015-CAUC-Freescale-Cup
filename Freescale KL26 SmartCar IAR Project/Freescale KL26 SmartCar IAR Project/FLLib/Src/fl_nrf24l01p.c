
#include "common.h"
#include "vcan_nrf24l0.h"
#include "fl_nrf24l01p.h"


uint8 buff[DATA_PACKET];//临时数据
uint8 data[DATA_PACKET];//接收数据
uint8 relen;

/************************************************************************/
/* 发送数据                                    20150107                 */
/************************************************************************/
void NrfSend(uint8 * str)
{
	FuncLocalShow("Hcsr04Init");
	sprintf((char *)buff, "%s", str);         //把str和i合并成一个字符串到buff里，再进行发送
	nrf_tx(buff, DATA_PACKET);                   //发送一个数据包：buff（包为32字节）
	//等待发送过程中，此处可以加入处理任务
	while (nrf_tx_state() == NRF_TXING);         //等待发送完成
	if (NRF_TX_OK == nrf_tx_state())
	{
		MessageShow("\n发送成功");
	}
	else
	{
		MessageShow("\n发送失败");
	}
}

/************************************************************************/
/*  查询接收                                     20150107               */
/************************************************************************/
void NrfRev()
{
	FuncLocalShow("Hcsr04Init");
	relen = nrf_rx(buff, DATA_PACKET);               //等待接收一个数据包，数据存储在buff里
	if (relen != 0)
	{
		sprintf((char*)data, "%s", buff);
	}
	else
	{
		data[0] = 0;//没收到数据。
	}
}



/*!
*  @brief      PORTC和D中断服务函数
*  @since      v5.0
*/
void PORTC_PORTD_IRQHandler()
{
	FuncLocalShow("Hcsr04Init");
	uint8  n = 0;    //引脚号
	//PTC18
	n = 18;
	if (PORTC_ISFR & (1 << n))           //PTC18触发中断
	{
		PORTC_ISFR = (1 << n);        //写1清中断标志位
		/*  以下为用户任务  */
		nrf_handler();
		/*  以上为用户任务  */
	}
}


/************************************************************************/
/* 初始化nrf24L01+                                                      */
/************************************************************************/
void NrfInit()
{
	FuncLocalShow("NrfInit");
	while (!nrf_init())                  //初始化NRF24L01+ ,等待初始化成功为止
	{
		printf("\n  nrf24L01+ connect failed\n");
	}
	set_vector_handler(PORTC_PORTD_VECTORn, PORTC_PORTD_IRQHandler);    			//设置 PORTE 的中断服务函数为 PORTE_VECTORn
	enable_irq(PORTC_PORTD_IRQn);
	MessageShow("NRF is connected");
	
}

