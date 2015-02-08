
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



#if 0//�ṹ�巽ʽʵ��
#if (TpmMotorPrecison > 255)
struct Speed_s
{
	uint16 Acturally;
	uint16 Expect;
	uint16 Max;
	uint16 Min;
};
#else
struct Speed_s
{
	uint8 Acturally;
	uint8 Expect;
	uint8 Max;
	uint8 Min;
};
#endif
#else//�ṹ��ͺ궨��ʵ��
#if (TpmMotorPrecison > 255)
struct Speed_s
{
	uint16 Acturally;
	uint16 Expect;
};
#else
struct Speed_s
{
	uint8 Acturally;
	uint8 Expect;
};
#endif
#define SpeedMax TpmMotorPrecison
#define SpeedMin 0
#endif




//uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold);

#endif//_FL_PID_


