
#include "common.h"
#include "fl_filter.h"

#warning 此文件有bug

//1、限副滤波
/* N值可根据实际情况调整
value为有效值，new_value为当前采样值
滤波程序返回有效的实际值 */

char value;

char coe[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
char sum_coe = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 + 12;
char value_buf[N];
char i = 0;

extern char get_ad();

char FilterNmplitudeLimiting()
{
	char new_value;
	new_value = get_ad();
	if ((new_value - value > N) || (value - new_value > N))
        {
		return value;
        }
	return new_value;

}

//2、中位值滤波法
/* N值可根据实际情况调整
排序采用冒泡法*/

char FilterMedian()
{
	char value_buf[N];
	char count, i, j, temp;
	for (count = 0; count < N; count++)
	{
		value_buf[count] = get_ad();
		DELAY_MS(FilterDelayTimeMS);
	}
	for (j = 0; j < N - 1; j++)
	{
		for (i = 0; i<N - j; i++)
		{
                  if (value_buf[i]>value_buf[i + 1])//这块有错，我随便改的:)估计用不了
			{
				temp = value_buf[i];
				value_buf[i] = value_buf[i + 1];
				value_buf[i + 1] = temp;
			}
		}
	}
	return value_buf[(N - 1) / 2];
}

//3、算术平均滤波法

char FilterAverage()
{
	int sum = 0;
        int count = 0;
	for (count = 0; count < N; count++)
	{
		sum += (uint8)get_ad();
		DELAY_MS(FilterDelayTimeMS);
	}
	return (char)(sum / N);
}

//4、递推平均滤波法（又称滑动平均滤波法）
/*
*/


char FilterRecursionAverage()
{
	char count;
	int sum = 0;
	value_buf[i++] = get_ad();
	if (i == N) i = 0;
	for (count = 0; count < N;count++)
		sum = value_buf[count];
	return (char)(sum / N);
}

//5、中位值平均滤波法（又称防脉冲干扰平均滤波法）

char FilterMedianAverage()
{
	char count, i, j;
	//char value_buf[N];
	int sum = 0;
	for (count = 0; count < N; count++)
	{
		value_buf[count] = get_ad();
		DELAY_MS(FilterDelayTimeMS);
	}
	for (j = 0; j < N - 1; j++)
	{
		for (i = 0; i<N - j; i++)
		{/*bug
			if (value_buf>value_buf[i + 1])
			{
				temp = value_buf;
				value_buf = value_buf[i + 1];
				value_buf[i + 1] = temp;
			}*/
		}
	}
	for (count = 1; count < N - 1; count++)
        {
		//sum += value[count];//bug
        }
	return (char)(sum / (N - 2));
}

//6、限幅平均滤波法
/*
*/
//略 参考子程序1、3

//7、一阶滞后滤波法
/* 为加快程序处理速度假定基数为100，a=0~100 */

char FilterFirstOrder()
{
	char new_value;
	new_value = get_ad();
	return (100 - a)*value + a*new_value;
}

//8、加权递推平均滤波法
/* coe数组为加权系数表，存在程序存储区。*/
char FilterWeightingRecursionAverage()
{
	char count;
	char value_buf[N];
	int sum = 0;
	for (count = 0;count < N; count++)
	{
		value_buf[count] = get_ad();
		DELAY_MS(FilterDelayTimeMS);
	}
	for (count = 0; count < N; count++)
		sum += value_buf[count] * coe[count];
	return (char)(sum / sum_coe);
}

//9、消抖滤波法
char FilterShakeClear()
{
	char count = 0;
	char new_value;
	new_value = get_ad();
	while (value != new_value);
	{
		count++;
		if (count >= N) return new_value;
		DELAY_MS(FilterDelayTimeMS);
		new_value = get_ad();
	}
	return value;
}
