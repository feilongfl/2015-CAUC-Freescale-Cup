#include "common.h"


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
struct Pid_s
{
	int32 Integral;//�����ۼ�ֵ
	int32 Now;//

	uint8 kp;
	uint8 ki;
	uint8 kd;

	int32 g;//������

	int32 Imax;//i�Ļ����޷�
	int32 Target;
	int32 last_error;//�ϴ����
};
#elif PidPrecision < 0xffff
struct Pid_s
{
	int32 Integral;//�����ۼ�ֵ
	int32 Now;//

	uint16 kp;
	uint16 ki;
	uint16 kd;

	int32 g;//������

	int32 Imax;//i�Ļ����޷�
	int32 Target;
	int32 last_error;//�ϴ����
};
#else
struct Pid_s
{
	int32 Integral;//�����ۼ�ֵ
	int32 Now;//

	uint32 kp;
	uint32 ki;
	uint32 kd;

	int32 g;//������

	int32 Imax;//i�Ļ����޷�
	int32 Target;
	int32 last_error;//�ϴ����
};
#endif


uint16 PID(struct Pid_s * maxwell);
//uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold);

#endif//_FL_PID_


