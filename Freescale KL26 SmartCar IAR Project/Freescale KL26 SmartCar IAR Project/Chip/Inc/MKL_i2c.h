/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       MK60_i2c.h
 * @brief      i2c驱动头文件
 * @author     山外科技
 * @version    v5.0
 * @date       2013-07-12
 * @note       目前仅实现主机读写寄存器功能，其他功能待实现
 */

#ifndef     __MK60_I2C_H__
#define     __MK60_I2C_H__
/**
 *  @brief I2C模块编号
 */
typedef enum
{
    I2C0  = 0,
    I2C1  = 1
} I2Cn_e;

/**
 *  @brief 主机读写模式选择
 */
typedef enum MSmode
{
    MWSR =   0x00,  /* 主机写模式  */
    MRSW =   0x01   /* 主机读模式  */
} MSmode;

extern I2C_MemMapPtr I2CN[2];

/*
*  把I2C通信的每个小步骤都用宏定义来实现，方便编写顶层函数
*  此宏定义参考飞思卡尔公司例程修改所得
*/
//启动信号
#define i2c_Start(I2Cn)             I2C_C1_REG(I2CN[I2Cn]) |= (I2C_C1_TX_MASK );I2C_C1_REG(I2CN[I2Cn]) |= ( I2C_C1_MST_MASK)     //MST 由0变1，产生起始信号，TX = 1 进入发送模式

//停止信号
#define i2c_Stop(I2Cn)              I2C_C1_REG(I2CN[I2Cn]) &= ~(I2C_C1_MST_MASK );I2C_C1_REG(I2CN[I2Cn]) &= ~(I2C_C1_TX_MASK) ;   //MST 由1变0，产生停止信号，TX = 0 进入接收模式

//重复启动
#define i2c_RepeatedStart(I2Cn)     I2C_C1_REG(I2CN[I2Cn]) |= I2C_C1_RSTA_MASK

//进入接收模式(应答,需要接收多个数据，接收最后一个字节前需要禁用应答i2c_DisableAck)
#define i2c_EnterRxMode(I2Cn)       I2C_C1_REG(I2CN[I2Cn]) &= ~(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK)  //

//进入接收模式(不应答,只接收一个字节)
#define i2c_PutinRxMode(I2Cn)       I2C_C1_REG(I2CN[I2Cn]) &= ~I2C_C1_TX_MASK;I2C_C1_REG(I2CN[I2Cn]) |= I2C_C1_TXAK_MASK

//禁用应答(接收最后一个字节)
#define i2c_DisableAck(I2Cn)        I2C_C1_REG(I2CN[I2Cn]) |= I2C_C1_TXAK_MASK

//等待 I2C_S
#define i2c_Wait(I2Cn)              while(( I2C_S_REG(I2CN[I2Cn]) & I2C_S_IICIF_MASK)==0) {} \
                                    I2C_S_REG(I2CN[I2Cn]) |= I2C_S_IICIF_MASK;

//判断是否应答了
#define i2c_IsAsk(I2Cn)             (( I2C_S_REG(I2CN[I2Cn])  & I2C_S_RXAK_MASK)==0 ? 1:0)

//写一个字节
#define i2c_write_byte(I2Cn,data)   (I2C_D_REG(I2CN[I2Cn]) = (data));


//目前代码仅支持 I2C主机模式
extern uint32  i2c_init(I2Cn_e i2cn, uint32 baud);                               //初始化I2C
extern void    i2c_write_reg(I2Cn_e, uint8 SlaveID, uint8 reg, uint8 Data);      //写入数据到寄存器
extern uint8   i2c_read_reg (I2Cn_e, uint8 SlaveID, uint8 reg);                  //读取寄存器的数据
extern void    i2c_write_reg_16(I2Cn_e, uint8 SlaveID, uint16 reg, uint8 Data);      //写入数据到寄存器
extern uint8   i2c_read_reg_16(I2Cn_e, uint8 SlaveID, uint16 reg);                  //读取寄存器的数据

#endif  //__MK60_I2C_H__
