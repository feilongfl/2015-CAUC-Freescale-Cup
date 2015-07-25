
#include "common.h"
#include "Vcan_led.h"
#include "fl_init.h"
#include "fl_include.h"
#include "main.h"


/************************************************************************/
/*                            ��ʼ��                                    */
/*                                                                      */
/*                                                                      */
/*     ����Ҫ��ʹ������ģ��֮ǰ���ô˺�����                             */
/*                                                  20150107            */
/************************************************************************/
InitRepot_e Init()
{
	led_init (LED_MAX);//��	
	tpm_pulse_init(TpmCoder, TpmCoderClkIn, TpmCoderPs);//������
	MotorPidInit();//���
	SteerPidInit();//���
	UartInit();
	PitInit();//��ʼ��pitģ��
	OlcdInit();//��ʼ��0.96OLEDҺ����
	NrfInit();//nrf24l01+
	FLKeyInit();//С����
	ConfigInit();//���ó�ʼ��
#if Car == Car2
	Hcsr04Init();
#endif //car
	return InitAllGreen;
}



