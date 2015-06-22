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

struct Pid_s
{
	int32 Integral;//�����ۼ�ֵ
	int32 Now;//

	uint16 P;
	uint16 I;
	uint16 D;

	int32 g;//������

	uint16 Imax;//i�Ļ����޷�
	int32 Target;
	int32 last_error;//�ϴ����
};


int32 PID(struct Pid_s * maxwell);
//uint32 Pid(uint32 Rin, uint32 Yout, float Kp, float Ki, float Kd, uint32 PidThreshold);

#endif//_FL_PID_


