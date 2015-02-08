
#include "common.h"
#include "Vcan_led.h"
#include "fl_init.h"
#include "fl_include.h"


/************************************************************************/
/*                            初始化                                    */
/*                                                                      */
/*                                                                      */
/*     你需要在使用所有模块之前调用此函数。                             */
/*                                                  20150107            */
/************************************************************************/
void Init ()
{
	FuncLocalShow("Init");

	led_init (LED_MAX);
	BludToothUartInit();//初始化蓝牙串口
	TpmInit();//初始化tpm模块
	SteerInit();
	PitInit();//初始化pit模块
	NrfInit();//初始化nrf24L01+模块
	Hcsr04Init();//初始化超声波模块
	OlcdInit();//初始化0.96OLED液晶屏
	FLKeyInit();//小键盘
	AdcInit();
}



