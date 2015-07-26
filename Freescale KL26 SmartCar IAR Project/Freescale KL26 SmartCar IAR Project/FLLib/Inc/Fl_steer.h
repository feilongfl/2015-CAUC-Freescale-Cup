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

//������Ʋ���
#define SteerTurnMax (SteerCenterDuty + SteerSafeTurnDuty)//���pwm���ֵ����
#define SteerTurnMin (SteerCenterDuty - SteerSafeTurnDuty)//���pwm��Сֵ����

#define SteerAngleProtectRange 200//���ҵ��ƫ��ֵ�ڴ˷�Χ���϶�Ϊֱ��
#define LostLineAdcMin 500//���е�й�һ������ֵ���ڴ�ֵ�϶�Ϊ����

/************************************************************************/
/*           �������Ͷ���                                                  */
/************************************************************************/
//#define SteerDegAbs
#ifdef SteerDegAbs
typedef uint8 SteerDeviationDegree_e;//ת��Ƕ�
#else
typedef int16 SteerDeviationDegree_e;//ת��Ƕ�
#endif

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
//void SteerTurn(SteerTurnDirection_e direction, SteerDeviationDegree_e degree);//ת��

//////////////////////////////////////////////////////////////////////////
void StreePidSet(Pid_e steerPid, uint8 steerPidChange);//�趨���pid����

SteerTurnDirection_e SteerDirectionSetByAdcOne(struct FLAdc_s * adc_s,FLAdcLostLine_e * lostLine);
SteerDeviationDegree_e SteerDeviationDegreeSetByAdc(struct FLAdc_s * adc_s);
void SteerVagueCtrl(int16 offset);

void SteerFuzzyDomainScan();
#endif//_FL_STEER_
