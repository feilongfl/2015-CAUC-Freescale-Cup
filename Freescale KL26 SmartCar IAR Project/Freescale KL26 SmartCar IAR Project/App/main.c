/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外KL26 平台主程序
 * @author     山外科技
 * @version    v5.2
 * @date       2014-10-26
 */

#include "common.h"
#include "include.h"

uint8  nrf_rx_buff[TSL1401_MAX*TSL1401_SIZE + 2*COM_LEN + DATA_PACKET];         //预多
uint8  nrf_tx_buff[TSL1401_MAX*TSL1401_SIZE + 2*COM_LEN + DATA_PACKET];         //预多

//函数声明
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT_IRQHandler();
void PORTC_PORTD_IRQHandler();

uint8  var1 = 20, var2;
uint16 var3, var4;
uint32 var5, var6;


/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note       山外 无线调试 测试实验
 */
void  main(void)
{
    uint32 i;
    com_e     com;
    nrf_result_e nrf_result;


    /************************ LCD 液晶屏 初始化  ***********************/
    LCD_init();

    /************************ 无线模块 NRF 初始化  ***********************/
    while(!nrf_init());
    //配置中断服务函数
    set_vector_handler(PORTC_PORTD_VECTORn ,PORTC_PORTD_IRQHandler);                //设置 PORTE 的中断服务函数为 PORTE_VECTORn
    enable_irq(PORTC_PORTD_IRQn);
    nrf_msg_init();                                                     //无线模块消息初始化

    //摄像头模块，需要 发送 空命令给 调试板模块，这样可以清掉 接收图像失败而产生多余数据
    i = 20;
    while(i--)
    {
        nrf_msg_tx(COM_RETRAN,nrf_tx_buff);                              //发送多个 空 命令过去，用于清空 接收端的缓存数据
    }

    /*********************** 按键消息 初始化  ***********************/
    key_event_init();                                                   //按键消息初始化
    pit_init_ms(PIT0,10);                                               //pit 定时中断(用于按键定时扫描)
    set_vector_handler(PIT_VECTORn ,PIT_IRQHandler);                  //设置 PIT0 的中断服务函数为 PIT0_IRQHandler
    enable_irq(PIT_IRQn);


    while(1)
    {
        /************************ 无线接收数据  ***********************/
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
        }while(nrf_result != NRF_RESULT_RX_NO);         //接收不到数据 才退出

        /*********************** 按键消息 处理  ***********************/
        deal_key_event();               //  此函数为 检查按键，并根据按键事件来修改 变量的值

        //此例程是 通过按键 改变变量的值。如果先 自己代码里修改变量的值，并发送出去，可参考如下帖子：
        //山外无线调试器如何接收并显示像速度这样的动态数据？？？求指导！！！ - 智能车讨论区 - 山外论坛 http://vcan123.com/forum.php?mod=viewthread&tid=4029&ctid=1

    }
}


/*!
 *  @brief      PORTC和D中断服务函数
 *  @since      v5.0
 */
void PORTC_PORTD_IRQHandler()
{
    uint8  n = 0;    //引脚号

    //PTC18
    n = 18;
    if(PORTC_ISFR & (1 << n))           //PTA6触发中断
    {
        PORTC_ISFR  = (1 << n);        //写1清中断标志位

        /*  以下为用户任务  */
        nrf_handler();

        /*  以上为用户任务  */
    }
}


/*!
 *  @brief      PIT0中断服务函数
 *  @since      v5.0
 */
void PIT_IRQHandler()
{
    if(PIT_TFLG(PIT0) == 1 )        //判断是否 PIT0 进入中断
    {
        key_IRQHandler();

        PIT_Flag_Clear(PIT0);
    }
}