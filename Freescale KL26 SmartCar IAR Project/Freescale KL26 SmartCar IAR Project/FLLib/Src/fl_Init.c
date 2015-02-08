
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
void Init ()
{
	FuncLocalShow("Init");

	led_init (LED_MAX);
	BludToothUartInit();//��ʼ����������
	TpmInit();//��ʼ��tpmģ��
	SteerInit();
	PitInit();//��ʼ��pitģ��
	NrfInit();//��ʼ��nrf24L01+ģ��
	Hcsr04Init();//��ʼ��������ģ��
	OlcdInit();//��ʼ��0.96OLEDҺ����
	FLKeyInit();//С����
	AdcInit();
}



