#ifndef _FL_Filter_
#define _FL_Filter_


#define A 10
#define N 12
#define a 50

#define FilterDelayTimeMS 10



//1���޸��˲�
/* Aֵ�ɸ���ʵ���������
valueΪ��Чֵ��new_valueΪ��ǰ����ֵ
�˲����򷵻���Ч��ʵ��ֵ */
char FilterAmplitudeLimiting();

//2����λֵ�˲���
/* Nֵ�ɸ���ʵ���������
�������ð�ݷ�*/

char FilterMedian();

//3������ƽ���˲���
char FilterAverage();
//4������ƽ���˲������ֳƻ���ƽ���˲�����
char FilterRecursionAverage();

//5����λֵƽ���˲������ֳƷ��������ƽ���˲�����

char FilterMedianAverage();

//6���޷�ƽ���˲���
/*
*/
//�� �ο��ӳ���1��3

//7��һ���ͺ��˲���
/* Ϊ�ӿ�������ٶȼٶ�����Ϊ100��a=0~100 */
char FilterFirstOrder();

//8����Ȩ����ƽ���˲���
/* coe����Ϊ��Ȩϵ�������ڳ���洢����*/
char FilterWeightingRecursionAverage();
//9�������˲���
char FilterShakeClear();


#endif//_FL_Filter_