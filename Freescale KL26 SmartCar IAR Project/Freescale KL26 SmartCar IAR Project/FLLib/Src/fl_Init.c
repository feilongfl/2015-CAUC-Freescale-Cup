
#include "common.h"
#include "Vcan_led.h"
#include "fl_init.h"
#include "fl_include.h"


/************************************************************************/
/*                            ��ʼ��                                    */
/*                                                                      */
/*                                                                      */
/*     ����Ҫ��ʹ������ģ��֮ǰ���ô˺�����                             */
/*                                                  20150107            */
/************************************************************************/
InitRepot_e Init()
{
	led_init (LED_MAX);
	SteerInit();
	tpm_pulse_init(TpmCoder, TpmCoderClkIn, TpmCoderPs);
	PitInit();//��ʼ��pitģ��
	Hcsr04Init();//��ʼ��������ģ��
	OlcdInit();//��ʼ��0.96OLEDҺ����
	NrfInit();//nrf24l01+
	FLKeyInit();//С����
	//ConfigInit();//���ó�ʼ��
	return InitAllGreen;
}



