#include "common.h"
#include "MKL_port.h"
#include "MKL_gpio.h"
#include "FL_Key.h"
#include "fl_settingmenu.h"
#include "main.h"


PTXn_e FLKeyPtxn[KeyMax][FLKeyPortNum] =
{
	{ KeyLine1, KeyRank1 }/*Kp*/, { KeyLine1, KeyRank2 }/*电机*/, { KeyLine1, KeyRank3 }/*up\+1*/, { KeyLine1, KeyRank4 }/*+10*/,
	{ KeyLine2, KeyRank1 }/*Ki*/, { KeyLine2, KeyRank2 }/*舵机*/, { KeyLine2, KeyRank3 }/*down\-1*/, { KeyLine2, KeyRank4 }/*-10*/,
	{ KeyLine3, KeyRank1 }/*Kd*/, { KeyLine3, KeyRank2 }/*speed*/, { KeyLine3, KeyRank3 }/*back*/, { KeyLine3, KeyRank4 }/*enter*/,
	{ KeyLine4, KeyRank1 }/*保留*/, { KeyLine4, KeyRank2 }/*归一化*/, { KeyLine4, KeyRank3 }/*reset*/, { KeyLine4, KeyRank4 }/*irq、菜单*/
};

PTXn_e FLKeyPort[KeyPortMax] =
{
	KeyLine1, KeyLine2, KeyLine3, KeyLine4,
	KeyRank1, KeyRank2, KeyRank3, KeyRank4
};

/************************************************************************/
/* 控制按键管教服复用                                                   */
/************************************************************************/
InitRepot_e    FLKeyInit()
{
	//ASSERT();//这里应该加一个断言

	//所有行列初始化为高电平,不接受按键事件，仅进行管脚复用
	//初始化为高电平
	for (uint8 keyPort = KeyLineNum; keyPort > 0;keyPort --)
	{
		gpio_init(FLKeyPort[keyPort - 1], GPO, HIGH);
		port_init_NoALT(FLKeyPort[keyPort - 1], PULLUP);
	}

	for (uint8 keyPort = KeyPortMax; keyPort > KeyLineNum; keyPort--)
	{
		gpio_init(FLKeyPort[keyPort - 1], GPI, HIGH);
		port_init_NoALT(FLKeyPort[keyPort - 1], PULLUP);
	}
	return InitAllGreen;
}

/*!
*  @brief      获取key状态（不带延时消抖）
*  @param      KEY_e           KEY编号
*  @return     KEY_STATUS_e    KEY状态（KEY_DOWN、KEY_DOWN）
*  Sample usage:
				if(key_get(KEY_U) ==  KEY_DOWN)
				{
				printf("\n按键按下")
				}
*/
KEY_STATUS_e FLKeyGet(FL_KEY_e key)
{
	gpio_set(FLKeyPtxn[key][FLKeyLine], LOW);//使能按键所在行
	DELAY_US(50);//小延时
	if (gpio_get(FLKeyPtxn[key][FLKeyRank]) == KEY_DOWN)//若触发按键所在列
	{
		gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//禁用按键所在行
		return KEY_DOWN;
	}
	else
	{
		gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//禁用按键所在行
		return KEY_UP;
	}
}


/*!
*  @brief      检测key状态（带延时消抖）
*  @param      KEY_e           KEY编号
*  @return     KEY_STATUS_e    KEY状态（KEY_UP、KEY_DOWN）
*  @since      v5.0
*  Sample usage:
if(key_check(KEY_U) ==  KEY_DOWN)
{
printf("\n按键按下")
}
*/
KEY_STATUS_e FLKeyCheck(FL_KEY_e key)
{
	gpio_set(FLKeyPtxn[key][FLKeyLine], LOW);//使能按键所在行
	DELAY_US(50);//小延时
	if (gpio_get(FLKeyPtxn[key][FLKeyRank]) == KEY_DOWN)//若触发按键所在列
	{
		DELAY_MS(10);//大延时
		if (gpio_get(FLKeyPtxn[key][FLKeyRank]) == KEY_DOWN)//若触发按键所在列
		{
			while (gpio_get(FLKeyPtxn[key][FLKeyRank]) == KEY_DOWN);//等待按键释放
			gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//禁用按键所在行
			return KEY_DOWN;
		}
		else
		{
			gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//禁用按键所在行
			return KEY_UP;
		}
	}
	else
	{
		gpio_set(FLKeyPtxn[key][FLKeyLine], HIGH);//禁用按键所在行
		return KEY_UP;
	}
}


/************************************************************************/
/* 允许接受irq指令                                                      */
/************************************************************************/
void FLKeyIrqEnable()
{
	//ASSERT();//这里应该加一个断言

	gpio_set(FLKeyPtxn[FLKeyIrq][FLKeyLine], LOW);//选中按键所在行
	port_init_NoALT(FLKeyPtxn[FLKeyIrq][FLKeyRank], IRQ_FALLING | PULLUP);//定义按键所在列 下降沿 触发中断,上拉电阻

	//KL26只有pta,和ptc，ptd可以配置中断，
	set_vector_handler(PORTC_PORTD_VECTORn, FLIrqHandle);    //设置PORTC和PORTD的中断服务函数为 PORTC_PORTD_IRQHandler
    enable_irq (PORTC_PORTD_IRQn);                                      //使能PORTC和PORTD中断
}

void FLKeyIrqDisable()
{
	disable_irq(PORTC_PORTD_IRQn);//关中断
	FLKeyInit();//拉高所有行列，禁用键盘
}

void FLIrqHandle()
{
#if IrqKeyPort == PortC//检测引脚配置
	//事实证明下面这么些是不行的
	//PORT_FUNC(IrqKeyPort, IrqKeyPortNum, FLIrqKeyDown);//执行设置中断

	//要这么写
	uint8  n = IrqKeyPortNum;    //引脚号
	if (PORTC_ISFR & (1 << n))           //PTC9 触发中断
	{
		PORTC_ISFR = (1 << n);        //写1清中断标志位
		/*  以下为用户任务  */
		FLKeyIrqDisable();
		if (FLKeyCheck(FLKeyIrq) == KEY_DOWN)//不加上这个手一碰就中断，我去了
		{
			tpm_pwm_duty(TpmMotor, TpmMotorCh0, 0);
			tpm_pwm_duty(TpmMotor, TpmMotorCh1, 0);
			while (FLKeyCheck(FLKeyIrq) == KEY_DOWN);
			FLIrqKeyDown();
		}
		FLKeyIrqEnable();
		/*  以上为用户任务  */

	}
#elif IrqKeyPort == PortD
	uint8  n = IrqKeyPortNum;    //引脚号
	n = 9;
	if (PORTD_ISFR & (1 << n))           //PTC9 触发中断
	{
		PORTD_ISFR = (1 << n);        //写1清中断标志位

		/*  以下为用户任务  */

		FLIrqKeyDown();

		/*  以上为用户任务  */
	}
#else//报错
#error The Reset Key Port is wrong!!
#endif
	extern void EndLine();
	//ptc14,干簧管
	n = 16;
	if (PORTC_ISFR & (1 << n))           //PTC18触发中断
	{
		PORTC_ISFR = (1 << n);        //写1清中断标志位

		/*  以下为用户任务  */
		EndLine();

		/*  以上为用户任务  */
	}

	//PTC18，nrf
	extern void nrf_handler();//麻烦了，这里竟然和nrf用了一个中断
	n = 18;
	if (PORTC_ISFR & (1 << n))           //PTC18触发中断
	{
		PORTC_ISFR = (1 << n);        //写1清中断标志位
		
		/*  以下为用户任务  */
		nrf_handler();

		/*  以上为用户任务  */
	}

	if (FreecaleConfig.Config.CarThis == MyCar2)
	{
		// 	extern void Hcsr04Irq();
		// 	n = 1;
		// 	if (PORTD_ISFR & (1 << n))          
		// 	{
		// 		PORTD_ISFR = (1 << n);        //写1清中断标志位
		// 
		// 		/*  以下为用户任务  */
		// 		extern void Hcsr04IrqPortIrq();
		// 		Hcsr04IrqPortIrq();
		// 		/*  以上为用户任务  */
		// 	}

		n = 1;
		if (PORTD_ISFR & (1 << n))           
		{
			PORTD_ISFR = (1 << n);        //写1清中断标志位

			/*  以下为用户任务  */
			extern void Hcsr04EchoIrq();
			Hcsr04EchoIrq();
			/*  以上为用户任务  */
		}
	}
}

/************************************************************************/
/* 设置                                                                 */
/************************************************************************/

FL_KEY_e KeyScan()//遍历所有按键
{
	while (TRUE)
	{
		for (uint8 keyTemp = 0; keyTemp < FLKeyMax; keyTemp++)
		{
			if (FLKeyCheck((FL_KEY_e)keyTemp) == KEY_DOWN)
			{
				return (FL_KEY_e)keyTemp;//终于等来了按键:)
			}
		}
	}
}

FL_KEY_e KeyScanWithoutIrq()//只扫描前三个键
{
	for (uint8 keyTemp = 0; keyTemp < 3; keyTemp++)
	{
		if (FLKeyCheck((FL_KEY_e)keyTemp) == KEY_DOWN)
		{
			return (FL_KEY_e)keyTemp;//终于等来了按键:)
		}
	}
	return FLNoKeyDown;
}


void FLIrqKeyDown()
{
	DisableInterrupts();
	FLKeyInit();//拉高所有引脚，禁用所有按键
	//显示屏进入设置模式
	SettingMenuInit();
}

