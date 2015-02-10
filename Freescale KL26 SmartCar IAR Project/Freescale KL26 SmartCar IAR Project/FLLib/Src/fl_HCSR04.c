
#include "common.h"
#include "fl_hcsr04.h"
#include "fl_olcd.h"

#ifdef MKL26Z4
#include "MKL_gpio.h"
#include "MKL_lptmr.h"
#elif MK60F15
#include "MK60_gpio.h"
#include "MK60_lptmr.h"
#elif MK60DZ10
#include "MK60_gpio.h"
#include "MK60_lptmr.h"
#endif

uint32 Distance;//���ڼ������
uint32 flag;//ָʾ�����Ƿ���Ч

/************************************************************************/
/* ������������                                      20150107           */
/* ��̳��ֱ���µģ���ûʽ�ܲ�����                                       */
/************************************************************************/
uint32 Hcsr04Read()
{
	flag = 0;
	gpio_set(Hcsr04Trig, 1);               //������������
	DELAY_US(15);
	gpio_set(Hcsr04Trig, 0);

	while (gpio_get(Hcsr04Echo) == 0);             //�ȴ���ƽ��ߣ��͵�ƽһֱ�ȴ�
	//pit_time_start(PIT0);                 //��ʼ��ʱ
	lptmr_time_start_us();//pit���������ˣ�����������ɣ���Դ������^��^
	while (gpio_get(Hcsr04Echo) == 1)              //�ȴ���ƽ��ͣ��ߵ�ƽһֱ�ȴ�
	{
		flag++;
		if (flag > Hcsr04FlagWait)
		{
			break;//�Ǻǣ������е�Զ
		}
	};
	Distance = lptmr_time_get_us();   //ֹͣ��ʱ����ȡ��ʱʱ��
	if (flag <Hcsr04FlagWait)
	{
		Distance = Distance * 340 / 2 / 1000;

		if (Distance > 5)
		{
			//printf("����Ϊ��%dmm\r\n", Distance); //��ӡ��ʱʱ��
			return Distance;
		}
	}
	return Hcsr04ReadFailed;
}
/************************************************************************/
/* ��������ʼ��                                            20150107     */
/************************************************************************/
InitRepot_e Hcsr04Init()
{
	gpio_init(Hcsr04Trig, GPO, 0);
	gpio_init(Hcsr04Echo, GPI, 0);
	return InitAllGreen;
}


void Hcsr04Show()
{
	
	if (Distance < 999)
	{
		NumShow(Distance, DistanceX, DistanceY);
	}
	else
	{
		NumShow(0, DistanceX, DistanceY);
	}
}

void Hcsr04ShowAutoRead()
{
	while (Distance == Hcsr04ReadFailed)
	{
		Distance = Hcsr04Read();
	}
	Hcsr04Show();
}