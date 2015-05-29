
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
4线SPI使用说明：
VBT 供内部DC-DC电压，3.3~4.3V，如果使用5V电压，为保险起见串一个100~500欧的电阻
VCC 供内部逻辑电压 1.8~6V
GND 地

BS0 低电平
BS1 低电平
BS2 低电平

CS  片选管脚
DC  命令数据选择管脚
RES 模块复位管脚
D0（SCLK） ，时钟脚，由MCU控制
D1（MOSI） ，主输出从输入数据脚，由MCU控制

D2 悬空
D3-D7 ， 低电平 ， 也可悬空，但最好设为低电平
RD  低电平 ，也可悬空，但最好设为低电平
RW  低电平 ，也可悬空，但最好设为低电平
RD  低电平 ，也可悬空，但最好设为低电平
*/

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xCF 

/************************************************************************/
/* 常量                                                                 */
/************************************************************************/
#define X_WIDTH 129
#define Y_WIDTH 64

#define byte unsigned char  
#define word unsigned int   


typedef enum //行号，貌似只能显示四行，大的显示屏，只是尺寸大了，字还是只能显示那么多
{
	LcdLine1 = 0,
	LcdLine2 = 2,//每行占两个 
	LcdLine3 = 4,
	LcdLine4 = 6,
}LcdLine_e;
/************************************************************************/
/* 菜单位置控制                                                         */
/************************************************************************/
#define LcdTitleLocal 0//标题左边距
#define LcdMenuLocal 0//菜单左边距

#define LcdTitleLine LcdLine1//标题位置

#define LcdMenuLine1 LcdLine2//菜单位置
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
}LcdAdcShowMaxOrMin_e;//adc输出最大、最小值

extern byte longqiu96x64[768];
/************************************************************************/
/* 初始化液晶屏                                                         */
/************************************************************************/
InitRepot_e OlcdInit(void);
/************************************************************************/
/*   清屏                                                               */
/************************************************************************/
void LcdCls(void);
/************************************************************************/
/* 显示数字，宽度不得超过三个字符                                       */
/************************************************************************/
void NumShow(uint16 num, uint8 x, uint8 y);
void NumShow16(uint16 num, uint8 x, uint8 y);
/****输出汉字和字符混合字符串******/
void LCDPrint(byte x, byte y, byte ch[]);
void LCDPrintInverse(byte x, byte y, byte ch[]);//反色


void LcdErrShow(LcdErr_e lcdErr);


#endif//_OLED_H_
