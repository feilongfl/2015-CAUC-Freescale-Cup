
#ifndef _FL_PID_
#define _FL_PID_


//pid枚举
typedef enum
{
	Kp,
	Ki,
	Kd,
}Pid_e;

#define PidPrecision 100//Pid精度

#if PidPrecision < 0xff//根据精度选择数据类型


struct Pid_s//pid结构体
{
	uint8 P;
	uint8 I;
	uint8 D;
};
#elif PidPrecision < 0xffff
struct Pid_s//pid结构体
{
	uint16 P;
	uint16 I;
	uint16 D;
};
#else
struct Pid_s//pid结构体
{
	uint32 P;
	uint32 I;
	uint32 D;
};
#endif






//uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold);

#endif//_FL_PID_


