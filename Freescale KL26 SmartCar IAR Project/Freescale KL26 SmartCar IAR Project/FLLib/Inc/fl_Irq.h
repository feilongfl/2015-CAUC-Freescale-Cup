#ifndef _FL_IRQ_
#define _FL_IRQ_

/************************************************************************/
/*       串口中断处理函数                                               */
/************************************************************************/
void UartHandler();

/************************************************************************/
/*                                                                      */
/************************************************************************/
void BlueToothHandler();

/************************************************************************/
/* PIT0中断函数                                         20150107        */
/************************************************************************/
void PIT_IRQHandler(void);

void FLIrqHandle();

#endif //_FL_IRQ_