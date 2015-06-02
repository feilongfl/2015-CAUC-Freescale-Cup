#include "fl_endline.h"
#include "fl_Motor.h"



void EndLine()
{
	if (key_check(Key_EndLine) != KEY_DOWN)
	{
		return;
	}
	else
	{
		Speed.Expect = 0;
	}
}
