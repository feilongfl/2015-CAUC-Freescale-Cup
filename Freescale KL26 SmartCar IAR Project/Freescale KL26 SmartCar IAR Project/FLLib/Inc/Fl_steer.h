/************************************************************************/
/*       ͷ�ļ�                                              */
/************************************************************************/
#include "common.h"
#include "fl_cfg.h"
#include "fl_pid.h"
#include "fl_ADC.h"


#ifndef _FL_STEER_
#define _FL_STEER_


/************************************************************************/
/*              �궨��                                               */
/************************************************************************/
//�����������
#define SteerCenterDuty 1500//�м�ֵ
#define SteerSafeTurnDuty 200//��Եֵ
//���Ĭ�ϲ���
#define SteerDefaultDuty SteerCenterDuty//�������
#define SteerPIDDefaultP 1//���Ĭ��P
#define SteerPIDDefaultI 1//���Ĭ��I
#define SteerPIDDefaultD 1//���Ĭ��D
//������Ʋ���
#define SteerTurnMax (SteerCenterDuty + SteerSafeTurnDuty)//���pwm���ֵ����
#define SteerTurnMin (SteerCenterDuty - SteerSafeTurnDuty)//���pwm��Сֵ����
#define SteerPidMaxP  1//������P
#define SteerPidMaxI  1//������I
#define SteerPidMaxD  1//������D
#define SteerPidMinP  0//�����СP
#define SteerPidMinI  0//�����СI
#define SteerPidMinD  0//�����СD

#define SteerAngleProtectRange 500//���ҵ��ƫ��ֵ�ڴ˷�Χ���϶�Ϊֱ��
#define LostLineAdcMin 200//���е�й�һ������ֵ���ڴ�ֵ�϶�Ϊ����

/************************************************************************/
/*           �������Ͷ���                                                  */
/************************************************************************/
typedef uint8 SteerDeviationDegree_e;//ת��Ƕ�

typedef enum
{
	SteerDirectionLeft,//��ת
	SteerDirectionCenter,//ֱ��
	SteerDirectionRight,//��ת
}SteerTurnDirection_e;//ת����



extern SteerTurnDirection_e CarDirection;

/************************************************************************/
/*         �ⲿ��������                                               */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
InitRepot_e SteerInit();//�����ʼ��������Ĭ��pwm

//////////////////////////////////////////////////////////////////////////
void SteerTurn(SteerTurnDirection_e direction, SteerDeviationDegree_e degree);//ת��

//////////////////////////////////////////////////////////////////////////
void StreePidSet(Pid_e steerPid, uint8 steerPidChange);//�趨���pid����

SteerTurnDirection_e SteerDirectionSetByAdcOne(struct FLAdc_s * adc_s);
SteerDeviationDegree_e SteerDeviationDegreeSetByAdc(struct FLAdc_s * adc_s);
#endif//_FL_STEER_
