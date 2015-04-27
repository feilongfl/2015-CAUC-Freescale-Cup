
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
InitRepot_e Init()
{
	led_init (LED_MAX);
	SteerInit();
	tpm_pulse_init(TpmCoder, TpmCoderClkIn, TpmCoderPs);
	PitInit();//初始化pit模块
	Hcsr04Init();//初始化超声波模块
	OlcdInit();//初始化0.96OLED液晶屏
	NrfInit();//nrf24l01+
	FLKeyInit();//小键盘
	//ConfigInit();//设置初始化
	return InitAllGreen;
}



