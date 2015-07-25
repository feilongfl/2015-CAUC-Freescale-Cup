#include "fl_math.h"


static void copyArr(uint16 * intArr, uint8 arrLength, uint16 * returnArr)//复制
{
	while (arrLength-- > 0)
	{
		*returnArr++ = *intArr++;
	}
}

static void swap(uint16 * intArr, uint16 * returnArr)
{
	uint16 temp = *intArr;
	*intArr = *returnArr;
	*returnArr = temp;
}


//c语言没有重载机制，先这么写吧，如果两个都有用就改下名字吧。
#if 1//是否保存至其他数组
//冒泡排序
static void BubbleSort(uint16 * uint16Arr, uint8 arrLength)
{
	uint16 * startLocal = uint16Arr;
	uint16 * stopLocal = uint16Arr + arrLength;
	for (uint8 sortTemp = arrLength; sortTemp > 0; sortTemp--)
	{
		while (uint16Arr != stopLocal)
		{
			if (*uint16Arr > *(uint16Arr + 1))
			{
				swap(uint16Arr, uint16Arr + 1);
			}
			uint16Arr++;
		}
		uint16Arr = startLocal;
	}
}
#else
//冒泡排序，并保存至returnarr
static void BubbleSort(uint16 * uint16Arr, uint8 arrLength,uint16 * returnArr)
{
	copyArr(uint16Arr, arrLength, returnArr);
	uint16 * startLocal = returnArr;
	uint16 * stopLocal = returnArr + arrLength;
	for (uint8 sortTemp = arrLength; sortTemp > 0; sortTemp--)
	{
		while (returnArr != stopLocal)
		{
			if (*returnArr > *(returnArr + 1))
			{
				swap(returnArr, returnArr + 1);
			}
			returnArr++;
		}
		returnArr = startLocal;
	}
}
#endif

//快速排序
static void QuickSort(uint16 * uint16Arr, uint8 arrLength, uint16 * returnArr)
{
	
}


//希尔排序
static void ShellSort(uint16 * uint16Arr, uint8 arrLength, uint16 * returnArr)
{

}

//简单选择排序
static void SimpleSelectionSort(uint16 * uint16Arr, uint8 arrLength, uint16 * returnArr)
{

}


//排序,数组地址，数组长度
struct SortExtremum_s ArrSort(uint16 * uint16Arr, uint8 arrLength)
{
	struct SortExtremum_s sortExtremum;
	BubbleSort(uint16Arr, arrLength);
	sortExtremum.Max = uint16Arr[0];
	sortExtremum.Min = uint16Arr[arrLength - 1];
	return sortExtremum;
}


uint32 POW(uint32 x, uint32 n)
{
	uint32 resault = x;
	while (n--)
	{
		resault *= 10;
	}
	return resault;
}
