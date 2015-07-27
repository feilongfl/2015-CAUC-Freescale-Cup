#include "common.h"
#include "fl_cfg.h"
#include "VCAN_key.h"

#ifndef _FL_endline_
#define _FL_endline_

#define EndLinePort PTC16

#define EndLineInit() key_init(Key_EndLine);port_init_NoALT(Key_EndLine,PULLUP | IRQ_FALLING)

void EndLine();

#endif//_FL_endline_
