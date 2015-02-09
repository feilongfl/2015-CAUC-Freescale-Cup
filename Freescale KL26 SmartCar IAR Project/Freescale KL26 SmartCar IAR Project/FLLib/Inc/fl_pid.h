
#ifndef _FL_PID_
#define _FL_PID_


//pidö��
typedef enum
{
	Kp,
	Ki,
	Kd,
}Pid_e;

#define PidPrecision 100//Pid����

#if PidPrecision < 0xff//���ݾ���ѡ����������


struct Pid_s//pid�ṹ��
{
	uint8 P;
	uint8 I;
	uint8 D;
};
#elif PidPrecision < 0xffff
struct Pid_s//pid�ṹ��
{
	uint16 P;
	uint16 I;
	uint16 D;
};
#else
struct Pid_s//pid�ṹ��
{
	uint32 P;
	uint32 I;
	uint32 D;
};
#endif






//uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold);

#endif//_FL_PID_


