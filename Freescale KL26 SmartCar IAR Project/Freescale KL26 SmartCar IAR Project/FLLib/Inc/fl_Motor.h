#include "common.h"
#include "fl_pid.h"
#include "fl_cfg.h"


//�����������
#define MotorDutyMax TpmMotorPrecison//���ֵ
//���Ĭ�ϲ���
#define SteerDefaultDuty 0//����
#define MotorPIDDefaultP 1//���Ĭ��P
#define MotorPIDDefaultI 1//���Ĭ��I
#define MotorPIDDefaultD 1//���Ĭ��D
//������Ʋ���
#define MotorPidMin_P  0//�����СP
#define MotorPidMin_I  0//�����СI
#define MotorPidMin_D  0//�����СD
#define MotorPidMax_P  1//������P
#define MotorPidMax_I  1//������I
#define MotorPidMax_D  1//������D



#if 0//�ṹ�巽ʽʵ��
#if (TpmMotorPrecison > 255)
struct MotorSpeed_s
{
	uint16 Acturally;
	uint16 Expect;
	uint16 Max;
	uint16 Min;
};
#else
struct MotorSpeed_s
{
	uint8 Acturally;
	uint8 Expect;
	uint8 Max;
	uint8 Min;
};
#endif
#else//�ṹ��ͺ궨��ʵ��
#if (TpmMotorPrecison > 255)
struct MotorSpeed_s
{
	uint16 Acturally;
	uint16 Expect;
};
#else
struct MotorSpeed_s
{
	uint8 Acturally;
	uint8 Expect;
};
#endif
#define MotorSpeedMax TpmMotorPrecison
#define MotorSpeedMin 0
#endif


/************************************************************************/
/*                                                                      */
/************************************************************************/
void MotorInit();//��ʼ�����
//////////////////////////////////////////////////////////////////////////