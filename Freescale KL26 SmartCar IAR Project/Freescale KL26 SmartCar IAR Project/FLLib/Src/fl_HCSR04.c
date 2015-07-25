
#include "common.h"
#include "fl_hcsr04.h"
#include "fl_olcd.h"

#ifdef MKL26Z4
#include "MKL_gpio.h"
#include "MKL_lptmr.h"
#include "MKL_adc.h"
#elif MK60F15
#include "MK60_gpio.h"
#include "MK60_lptmr.h"
#elif MK60DZ10
#include "MK60_gpio.h"
#include "MK60_lptmr.h"
#endif

uint32 Distance;//用于计算距离
uint32 flag;//指示数据是否有效

/************************************************************************/
/* 读超声波数据                                      20150107           */
/* 论坛上直接下的，还没式能不能用                                       */
/************************************************************************/
uint32 Hcsr04Read()
{
	flag = 0;
// 	gpio_set(Hcsr04Trig, 1);               //产生触发脉冲
// 	DELAY_US(15);
// 	gpio_set(Hcsr04Trig, 0);

	while (gpio_get(Hcsr04Irq));//wait for trig

	while (gpio_get(Hcsr04Echo) == 0);             //等待电平变高，低电平一直等待
	//pit_time_start(PIT0);                 //开始计时
	lptmr_time_start_us();//pit被我拿走了，这块就用这个吧，资源不够啊^…^
	while (gpio_get(Hcsr04Echo) == 1)              //等待电平变低，高电平一直等待
	{
		flag++;
		if (flag > Hcsr04FlagWait)
		{
			break;//呵呵，距离有点远
		}
	};
	Distance = lptmr_time_get_us();   //停止计时，获取计时时间
	if (flag <Hcsr04FlagWait)
	{
		Distance = Distance * 340 / 2 / 1000;

		if (Distance > 5)
		{
			//printf("距离为：%dmm\r\n", Distance); //打印延时时间
			return Distance;
		}
	}
	return Hcsr04ReadFailed;
}
/************************************************************************/
/* 超声波初始化                                            20150107     */
/************************************************************************/
#if UseSoundSpeedByTemperature
uint16 SoundSpeed = 0;//声速
#endif //UseSoundSpeedByTemperature

InitRepot_e Hcsr04Init()
{
	gpio_init(Hcsr04Irq, GPI, 0);//use gpi mode 
	port_init_NoALT(Hcsr04Irq, IRQ_EITHER | PULLDOWN);//定义按键所在列 跳变沿中断 下拉电阻
	gpio_init(Hcsr04Echo, GPI, 0);
	port_init_NoALT(Hcsr04Irq, IRQ_EITHER | PULLDOWN);//定义按键所在列 跳变沿中断 下拉电阻

#if UseSoundSpeedByTemperature
	adc_init(Temp0_Sensor);

	uint16 Temperature = 0;
	for (uint8 i = 8; i > 0; i--)
	{
		Temperature += adc_once(Temp0_Sensor);
	}
	Temperature >>= 3;//除8

	SoundSpeed = (uint16)(Temperature*0.067 + 331.5)

	//声速=331.5+0.607*温度
#endif //UseSoundSpeedByTemperature

	return InitAllGreen;
}

void Hcsr04IrqPortIrq()
{
	lptmr_time_start_ms();
}

extern uint32 CarDistance;

void Hcsr04EchoIrq()
{
	uint32 dis = lptmr_time_get_ms();

	if (dis != ~0)//没溢出
	{
#if UseSoundSpeedByTemperature
		dis = dis * SoundSpeed / 2 / 1000;
#else
		dis = dis * 340 / 2 / 1000;

#endif //UseSoundSpeedByTemperature
		if (dis < 50)//没超过最大距离（340m/s * 0.02s = 6.8m = 68dm)
		{
			CarDistance = dis;
		}
	}
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