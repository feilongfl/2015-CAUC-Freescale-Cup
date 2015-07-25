#include "common.h"
#include "fl_cfg.h"

#ifndef _FL_math_
#define _FL_math_


struct SortExtremum_s //用于存储排序后的结果
{
	uint16 Max;//最大值
	uint16 Min;//最小值
	//uint16 MaxLocal;//最大值位置
	//uint16 MinLocal;//最小值位置
};

struct SortExtremum_s ArrSort(uint16 * uint16Arr, uint8 arrLength);
uint32 POW(uint32 x, uint8 n);

#endif//_FL_math_
