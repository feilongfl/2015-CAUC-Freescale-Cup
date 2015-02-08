#ifndef _FL_Filter_
#define _FL_Filter_


#define A 10
#define N 12
#define a 50

#define FilterDelayTimeMS 10



//1、限副滤波
/* A值可根据实际情况调整
value为有效值，new_value为当前采样值
滤波程序返回有效的实际值 */
char FilterAmplitudeLimiting();

//2、中位值滤波法
/* N值可根据实际情况调整
排序采用冒泡法*/

char FilterMedian();

//3、算术平均滤波法
char FilterAverage();
//4、递推平均滤波法（又称滑动平均滤波法）
char FilterRecursionAverage();

//5、中位值平均滤波法（又称防脉冲干扰平均滤波法）

char FilterMedianAverage();

//6、限幅平均滤波法
/*
*/
//略 参考子程序1、3

//7、一阶滞后滤波法
/* 为加快程序处理速度假定基数为100，a=0~100 */
char FilterFirstOrder();

//8、加权递推平均滤波法
/* coe数组为加权系数表，存在程序存储区。*/
char FilterWeightingRecursionAverage();
//9、消抖滤波法
char FilterShakeClear();


#endif//_FL_Filter_