#include "common.h"
#include "fl_cfg.h"

#ifndef _FL_math_
#define _FL_math_


struct SortExtremum_s //���ڴ洢�����Ľ��
{
	uint16 Max;//���ֵ
	uint16 Min;//��Сֵ
	//uint16 MaxLocal;//���ֵλ��
	//uint16 MinLocal;//��Сֵλ��
};

struct SortExtremum_s ArrSort(uint16 * uint16Arr, uint8 arrLength);

#endif//_FL_math_
