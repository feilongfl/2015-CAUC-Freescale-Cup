
#include "common.h"
#include "fl_filter.h"

#warning ���ļ���bug

//1���޸��˲�
/* Nֵ�ɸ���ʵ���������
valueΪ��Чֵ��new_valueΪ��ǰ����ֵ
�˲����򷵻���Ч��ʵ��ֵ */

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

//2����λֵ�˲���
/* Nֵ�ɸ���ʵ���������
�������ð�ݷ�*/

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
                  if (value_buf[i]>value_buf[i + 1])//����д������ĵ�:)�����ò���
			{
				temp = value_buf[i];
				value_buf[i] = value_buf[i + 1];
				value_buf[i + 1] = temp;
			}
		}
	}
	return value_buf[(N - 1) / 2];
}

//3������ƽ���˲���

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

//4������ƽ���˲������ֳƻ���ƽ���˲�����
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

//5����λֵƽ���˲������ֳƷ��������ƽ���˲�����

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

//6���޷�ƽ���˲���
/*
*/
//�� �ο��ӳ���1��3

//7��һ���ͺ��˲���
/* Ϊ�ӿ�������ٶȼٶ�����Ϊ100��a=0~100 */

char FilterFirstOrder()
{
	char new_value;
	new_value = get_ad();
	return (100 - a)*value + a*new_value;
}

//8����Ȩ����ƽ���˲���
/* coe����Ϊ��Ȩϵ�������ڳ���洢����*/
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

//9�������˲���
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
