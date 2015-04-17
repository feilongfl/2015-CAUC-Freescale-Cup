#include "fl_eeprom.h"


void EepromInit()
{
	i2c_init(EEPROMI2C, EEPROMBaud);
}

void EepromWrite(uint16 reg, uint8 data)
{
	i2c_Start(EEPROMI2C);                                    //���������ź�

	i2c_write_byte(EEPROMI2C, (EEPROMAddress << 1) | MWSR);      //���ʹӻ���ַ��дλ
	i2c_Wait(EEPROMI2C);
	if (i2c_IsAsk(EEPROMI2C) == 0) return;                  //û��Ӧ��

	i2c_write_byte(EEPROMI2C, (uint8)(reg >> 8));          //���ʹӻ���ļĴ�����ַ�߰�λ
	i2c_Wait(EEPROMI2C);

	i2c_write_byte(EEPROMI2C, (uint8)reg);                //���ʹӻ���ļĴ�����ַ
	i2c_Wait(EEPROMI2C);

	i2c_write_byte(EEPROMI2C, data);                         //������Ҫд�������
	i2c_Wait(EEPROMI2C);

	i2c_Stop(EEPROMI2C);

	DELAY_MS(DelayTime);                                            //��ʱ̫�̵Ļ�������д����
}

uint8 EepromRead(uint16 reg)
{
	//��д��Ĵ�����ַ,�ٶ�ȡ����,��˴˹����� I2C �ĸ��ϸ�ʽ,�ı����ݷ���ʱ��Ҫ��������
	uint8 result;

	i2c_Start(EEPROMI2C);                                    //���������ź�

	i2c_write_byte(EEPROMI2C, (EEPROMAddress << 1) | MWSR);      //���ʹӻ���ַ��дλ
	i2c_Wait(EEPROMI2C);

	i2c_write_byte(EEPROMI2C, (uint8)(reg >> 8));                          //���ʹӻ���ļĴ�����ַ�߰�λ
	i2c_Wait(EEPROMI2C);

	i2c_write_byte(EEPROMI2C, (uint8)reg);                          //���ʹӻ���ļĴ�����ַ�Ͱ�λ
	i2c_Wait(EEPROMI2C);

	i2c_RepeatedStart(EEPROMI2C);                            //���ϸ�ʽ���������������ź�
        
	i2c_write_byte(EEPROMI2C, (EEPROMAddress << 1) | MRSW);      //���ʹӻ���ַ�Ͷ�λ
	i2c_Wait(EEPROMI2C);

	//i2c_EnterRxMode(EEPROMI2C) ;
	i2c_PutinRxMode(EEPROMI2C);                              //�������ģʽ(��Ӧ��,ֻ����һ���ֽ�)


	result = I2C_D_REG(I2CN[EEPROMI2C]);                     //��ٶ�ȡһ�Σ�������������
	i2c_Wait(EEPROMI2C);                                     //�ȴ��������

	i2c_Stop(EEPROMI2C);                                     //����ֹͣ�ź�

	result = I2C_D_REG(I2CN[EEPROMI2C]);                     //��ȡ����

	DELAY_MS(DelayTime);                                            //������ʱһ�£��������

	return result;
}