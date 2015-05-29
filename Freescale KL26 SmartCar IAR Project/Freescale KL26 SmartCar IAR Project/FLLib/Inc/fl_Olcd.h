
#include "common.h"
#include "fl_error.h"
#ifdef MKL26Z4
#include "MKL_gpio.h"
#elif MK60F15
#include "MK60_gpio.h
#elif  _FL_VISUAL_STUDIO_
#include "MKL_gpio.h"
#elif MK60DZ10
#include "MK60_gpio.h"
#endif
//#include "fl_ADC.h"


#ifndef _OLED_H_
#define _OLED_H_



/*
4��SPIʹ��˵����
VBT ���ڲ�DC-DC��ѹ��3.3~4.3V�����ʹ��5V��ѹ��Ϊ���������һ��100~500ŷ�ĵ���
VCC ���ڲ��߼���ѹ 1.8~6V
GND ��

BS0 �͵�ƽ
BS1 �͵�ƽ
BS2 �͵�ƽ

CS  Ƭѡ�ܽ�
DC  ��������ѡ��ܽ�
RES ģ�鸴λ�ܽ�
D0��SCLK�� ��ʱ�ӽţ���MCU����
D1��MOSI�� ����������������ݽţ���MCU����

D2 ����
D3-D7 �� �͵�ƽ �� Ҳ�����գ��������Ϊ�͵�ƽ
RD  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
RW  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
RD  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
*/

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xCF 

/************************************************************************/
/* ����                                                                 */
/************************************************************************/
#define X_WIDTH 129
#define Y_WIDTH 64

#define byte unsigned char  
#define word unsigned int   


typedef enum //�кţ�ò��ֻ����ʾ���У������ʾ����ֻ�ǳߴ���ˣ��ֻ���ֻ����ʾ��ô��
{
	LcdLine1 = 0,
	LcdLine2 = 2,//ÿ��ռ���� 
	LcdLine3 = 4,
	LcdLine4 = 6,
}LcdLine_e;
/************************************************************************/
/* �˵�λ�ÿ���                                                         */
/************************************************************************/
#define LcdTitleLocal 0//������߾�
#define LcdMenuLocal 0//�˵���߾�

#define LcdTitleLine LcdLine1//����λ��

#define LcdMenuLine1 LcdLine2//�˵�λ��
#define LcdMenuLine2 LcdLine3
#define LcdMenuLine3 LcdLine4



#define LcdLocal1 0
#define LcdLocal2 30
#define LcdLocal3 60
#define LcdLocal4 90

#define LcdLine 0
#define LcdLocal 1

typedef enum 
{
	LcdShowMax,
	LcdShowMin,
}LcdAdcShowMaxOrMin_e;//adc��������Сֵ

extern byte longqiu96x64[768];
/************************************************************************/
/* ��ʼ��Һ����                                                         */
/************************************************************************/
InitRepot_e OlcdInit(void);
/************************************************************************/
/*   ����                                                               */
/************************************************************************/
void LcdCls(void);
/************************************************************************/
/* ��ʾ���֣���Ȳ��ó��������ַ�                                       */
/************************************************************************/
void NumShow(uint16 num, uint8 x, uint8 y);
void NumShow16(uint16 num, uint8 x, uint8 y);
/****������ֺ��ַ�����ַ���******/
void LCDPrint(byte x, byte y, byte ch[]);
void LCDPrintInverse(byte x, byte y, byte ch[]);//��ɫ


void LcdErrShow(LcdErr_e lcdErr);


#endif//_OLED_H_
