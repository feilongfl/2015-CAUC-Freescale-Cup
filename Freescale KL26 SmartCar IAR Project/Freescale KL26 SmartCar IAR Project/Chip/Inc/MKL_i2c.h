/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       MK60_i2c.h
 * @brief      i2c����ͷ�ļ�
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-07-12
 * @note       Ŀǰ��ʵ��������д�Ĵ������ܣ��������ܴ�ʵ��
 */

#ifndef     __MK60_I2C_H__
#define     __MK60_I2C_H__
/**
 *  @brief I2Cģ����
 */
typedef enum
{
    I2C0  = 0,
    I2C1  = 1
} I2Cn_e;

/**
 *  @brief ������дģʽѡ��
 */
typedef enum MSmode
{
    MWSR =   0x00,  /* ����дģʽ  */
    MRSW =   0x01   /* ������ģʽ  */
} MSmode;

extern I2C_MemMapPtr I2CN[2];

/*
*  ��I2Cͨ�ŵ�ÿ��С���趼�ú궨����ʵ�֣������д���㺯��
*  �˺궨��ο���˼������˾�����޸�����
*/
//�����ź�
#define i2c_Start(I2Cn)             I2C_C1_REG(I2CN[I2Cn]) |= (I2C_C1_TX_MASK );I2C_C1_REG(I2CN[I2Cn]) |= ( I2C_C1_MST_MASK)     //MST ��0��1��������ʼ�źţ�TX = 1 ���뷢��ģʽ

//ֹͣ�ź�
#define i2c_Stop(I2Cn)              I2C_C1_REG(I2CN[I2Cn]) &= ~(I2C_C1_MST_MASK );I2C_C1_REG(I2CN[I2Cn]) &= ~(I2C_C1_TX_MASK) ;   //MST ��1��0������ֹͣ�źţ�TX = 0 �������ģʽ

//�ظ�����
#define i2c_RepeatedStart(I2Cn)     I2C_C1_REG(I2CN[I2Cn]) |= I2C_C1_RSTA_MASK

//�������ģʽ(Ӧ��,��Ҫ���ն�����ݣ��������һ���ֽ�ǰ��Ҫ����Ӧ��i2c_DisableAck)
#define i2c_EnterRxMode(I2Cn)       I2C_C1_REG(I2CN[I2Cn]) &= ~(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK)  //

//�������ģʽ(��Ӧ��,ֻ����һ���ֽ�)
#define i2c_PutinRxMode(I2Cn)       I2C_C1_REG(I2CN[I2Cn]) &= ~I2C_C1_TX_MASK;I2C_C1_REG(I2CN[I2Cn]) |= I2C_C1_TXAK_MASK

//����Ӧ��(�������һ���ֽ�)
#define i2c_DisableAck(I2Cn)        I2C_C1_REG(I2CN[I2Cn]) |= I2C_C1_TXAK_MASK

//�ȴ� I2C_S
#define i2c_Wait(I2Cn)              while(( I2C_S_REG(I2CN[I2Cn]) & I2C_S_IICIF_MASK)==0) {} \
                                    I2C_S_REG(I2CN[I2Cn]) |= I2C_S_IICIF_MASK;

//�ж��Ƿ�Ӧ����
#define i2c_IsAsk(I2Cn)             (( I2C_S_REG(I2CN[I2Cn])  & I2C_S_RXAK_MASK)==0 ? 1:0)

//дһ���ֽ�
#define i2c_write_byte(I2Cn,data)   (I2C_D_REG(I2CN[I2Cn]) = (data));


//Ŀǰ�����֧�� I2C����ģʽ
extern uint32  i2c_init(I2Cn_e i2cn, uint32 baud);                               //��ʼ��I2C
extern void    i2c_write_reg(I2Cn_e, uint8 SlaveID, uint8 reg, uint8 Data);      //д�����ݵ��Ĵ���
extern uint8   i2c_read_reg (I2Cn_e, uint8 SlaveID, uint8 reg);                  //��ȡ�Ĵ���������
extern void    i2c_write_reg_16(I2Cn_e, uint8 SlaveID, uint16 reg, uint8 Data);      //д�����ݵ��Ĵ���
extern uint8   i2c_read_reg_16(I2Cn_e, uint8 SlaveID, uint16 reg);                  //��ȡ�Ĵ���������

#endif  //__MK60_I2C_H__
