
#include "common.h"
#include "fl_pit.h"

#ifdef MKL26Z4
#include "MKL_pit.h"
#elif MK60F15
#include "MK60_pit.h"
#elif MK60DZ10
#include "MK60_pit.h"
#endif

extern void PIT_IRQHandler();
/************************************************************************/
/*      初始化                                         20150107         */
/************************************************************************/
InitRepot_e PitInit()
{
	pit_init_ms(CoderPit, CoderTimeCircle);                                //初始化PIT0，定时时间为： 1000ms
	set_vector_handler(PIT_VECTORn, PIT_IRQHandler);       //设置PIT0的中断服务函数为 PIT_IRQHandler
	return InitAllGreen;
}


