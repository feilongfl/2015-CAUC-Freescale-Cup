#include "fl_math.h"


static void copyArr(uint16 * intArr, uint8 arrLength, uint16 * returnArr)//����
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


//c����û�����ػ��ƣ�����ôд�ɣ�������������þ͸������ְɡ�
#if 1//�Ƿ񱣴�����������
//ð������
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
//ð�����򣬲�������returnarr
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

//��������
static void QuickSort(uint16 * uint16Arr, uint8 arrLength, uint16 * returnArr)
{
	
}


//ϣ������
static void ShellSort(uint16 * uint16Arr, uint8 arrLength, uint16 * returnArr)
{

}

//��ѡ������
static void SimpleSelectionSort(uint16 * uint16Arr, uint8 arrLength, uint16 * returnArr)
{

}


//����,�����ַ�����鳤��
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
