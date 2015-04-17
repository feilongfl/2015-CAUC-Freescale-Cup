#include "common.h"
#include "fl_cfg.h"
#include "MKL_i2c.h"
#include "MKL_gpio.h"

#ifndef _FL_eeprom_
#define _FL_eeprom_

#define AT24C02 0
#define AT24C256 1

#define EEPROMTYPE AT24C256

#define EEPROMI2C I2C0
#define EEPROMBaud (100 * 1000)

#if (EEPROMTYPE == AT24C256)
#define A0	LOW
#define A1  LOW

#define EEPROMAddress ((0x50)|(((A1)<<1)|(A0)))
#else
#error eeprom type error!
#endif

#define DelayTime 3

#if 0
#define Eeprom_init()			i2c_init(EEPROMI2C, EEPROMBaud)
#define EepromWrite(reg,data)	i2c_write_reg_16(EEPROMI2C, EEPROMAddress, (reg),  (Data));      //写入数据到寄存器
#define EepromRead(reg)			i2c_read_reg_16(EEPROMI2C, EEPROMAddress,(reg));                  //读取寄存器的数据
#else
extern void EepromInit();
extern void EepromWrite(uint16 reg, uint8 data);
extern uint8 EepromRead(uint16 reg);
#endif

#endif//_FL_eeprom_
