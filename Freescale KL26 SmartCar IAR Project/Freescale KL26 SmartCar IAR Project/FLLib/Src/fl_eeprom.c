#include "fl_eeprom.h"


void EepromInit()
{
	i2c_init(EEPROMI2C, EEPROMBaud);
}

void EepromWrite(uint16 reg, uint8 data)
{
	i2c_Start(EEPROMI2C);                                    //发送启动信号

	i2c_write_byte(EEPROMI2C, (EEPROMAddress << 1) | MWSR);      //发送从机地址和写位
	i2c_Wait(EEPROMI2C);
	if (i2c_IsAsk(EEPROMI2C) == 0) return;                  //没有应答

	i2c_write_byte(EEPROMI2C, (uint8)(reg >> 8));          //发送从机里的寄存器地址高八位
	i2c_Wait(EEPROMI2C);

	i2c_write_byte(EEPROMI2C, (uint8)reg);                //发送从机里的寄存器地址
	i2c_Wait(EEPROMI2C);

	i2c_write_byte(EEPROMI2C, data);                         //发送需要写入的数据
	i2c_Wait(EEPROMI2C);

	i2c_Stop(EEPROMI2C);

	DELAY_MS(DelayTime);                                            //延时太短的话，可能写出错
}

uint8 EepromRead(uint16 reg)
{
	//先写入寄存器地址,再读取数据,因此此过程是 I2C 的复合格式,改变数据方向时需要重新启动
	uint8 result;

	i2c_Start(EEPROMI2C);                                    //发送启动信号

	i2c_write_byte(EEPROMI2C, (EEPROMAddress << 1) | MWSR);      //发送从机地址和写位
	i2c_Wait(EEPROMI2C);

	i2c_write_byte(EEPROMI2C, (uint8)(reg >> 8));                          //发送从机里的寄存器地址高八位
	i2c_Wait(EEPROMI2C);

	i2c_write_byte(EEPROMI2C, (uint8)reg);                          //发送从机里的寄存器地址低八位
	i2c_Wait(EEPROMI2C);

	i2c_RepeatedStart(EEPROMI2C);                            //复合格式，发送重新启动信号
        
	i2c_write_byte(EEPROMI2C, (EEPROMAddress << 1) | MRSW);      //发送从机地址和读位
	i2c_Wait(EEPROMI2C);

	//i2c_EnterRxMode(EEPROMI2C) ;
	i2c_PutinRxMode(EEPROMI2C);                              //进入接收模式(不应答,只接收一个字节)


	result = I2C_D_REG(I2CN[EEPROMI2C]);                     //虚假读取一次，启动接收数据
	i2c_Wait(EEPROMI2C);                                     //等待接收完成

	i2c_Stop(EEPROMI2C);                                     //发送停止信号

	result = I2C_D_REG(I2CN[EEPROMI2C]);                     //读取数据

	DELAY_MS(DelayTime);                                            //必须延时一下，否则出错

	return result;
}