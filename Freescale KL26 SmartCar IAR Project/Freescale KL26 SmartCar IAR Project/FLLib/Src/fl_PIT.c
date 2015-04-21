
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
/*      ��ʼ��                                         20150107         */
/************************************************************************/
InitRepot_e PitInit()
{
	pit_init_ms(CoderPit, CoderTimeCircle);                                //��ʼ��PIT0����ʱʱ��Ϊ�� 1000ms
	set_vector_handler(PIT_VECTORn, PIT_IRQHandler);       //����PIT0���жϷ�����Ϊ PIT_IRQHandler
	return InitAllGreen;
}


