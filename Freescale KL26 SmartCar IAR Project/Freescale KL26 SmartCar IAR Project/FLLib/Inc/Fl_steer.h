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

/************************************************************************/
/*           �������Ͷ���                                                  */
/************************************************************************/
typedef enum
{
	SteerDegree0,//0��,����ֱ��
	SteerDegree1,//1��
	SteerDegree2,//2��
	SteerDegree3,//3��
	SteerDegree4,//4��
	SteerDegree5,//5��
	SteerDegree6,//6��
	SteerDegree7,//7��
	SteerDegree8,//8��
	SteerDegree9,//9��
	SteerDegree10,//10��
	SteerDegree11,//11��
	SteerDegree12,//12��
	SteerDegree13,//13��
	SteerDegree14,//14��
	SteerDegree15,//15��
	SteerDegree16,//16��
	SteerDegree17,//17��
	SteerDegree18,//18��
	SteerDegree19,//19��
	SteerDegree20,//20��
	SteerDegree21,//21��
	SteerDegree22,//22��
	SteerDegree23,//23��
	SteerDegree24,//24��
	SteerDegree25,//25��
	SteerDegree26,//26��
	SteerDegree27,//27��
	SteerDegree28,//28��
	SteerDegree29,//29��
	SteerDegree30,//30��
	SteerDegree31,//31��
	SteerDegree32,//32��
	SteerDegree33,//33��
	SteerDegree34,//34��
	SteerDegree35,//35��
	SteerDegree36,//36��
	SteerDegree37,//37��
	SteerDegree38,//38��
	SteerDegree39,//39��
	SteerDegree40,//40��
	/*
	SteerDegree41,//41��
	SteerDegree42,//42��
	SteerDegree43,//43��
	SteerDegree44,//44��
	SteerDegree45,//45��
	SteerDegree46,//46��
	SteerDegree47,//47��
	SteerDegree48,//48��
	SteerDegree49,//49��
	SteerDegree50,//50��
	SteerDegree51,//51��
	SteerDegree52,//52��
	SteerDegree53,//53��
	SteerDegree54,//54��
	SteerDegree55,//55��
	SteerDegree56,//56��
	SteerDegree57,//57��
	SteerDegree58,//58��
	SteerDegree59,//59��
	SteerDegree60,//60��
	SteerDegree61,//61��
	SteerDegree62,//62��
	SteerDegree63,//63��
	SteerDegree64,//64��
	SteerDegree65,//65��
	SteerDegree66,//66��
	SteerDegree67,//67��
	SteerDegree68,//68��
	SteerDegree69,//69��
	SteerDegree70,//70��
	SteerDegree71,//71��
	SteerDegree72,//72��
	SteerDegree73,//73��
	SteerDegree74,//74��
	SteerDegree75,//75��
	SteerDegree76,//76��
	SteerDegree77,//77��
	SteerDegree78,//78��
	SteerDegree79,//79��
	SteerDegree80,//80��
	SteerDegree81,//81��
	SteerDegree82,//82��
	SteerDegree83,//83��
	SteerDegree84,//84��
	SteerDegree85,//85��
	SteerDegree86,//86��
	SteerDegree87,//87��
	SteerDegree88,//88��
	SteerDegree89,//89��
	SteerDegree90,//90��
	�ų�����Ƕ�
	*/
	SteerDegreeNum,//��Ա��
}SteerTurnDegree_e;//ת��Ƕ�

typedef enum
{
	SteerDirectionLeft,//��ת
	SteerDirectionCenter,//ֱ��
	SteerDirectionRight,//��ת
}SteerTurnDirection_e;//ת����



//extern SteerTurnDirection_e CarDirection;

/************************************************************************/
/*         �ⲿ��������                                               */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
InitRepot_e SteerInit();//�����ʼ��������Ĭ��pwm

//////////////////////////////////////////////////////////////////////////
void SteerTurn(SteerTurnDirection_e direction, SteerTurnDegree_e degree);//ת��

//////////////////////////////////////////////////////////////////////////
void StreePidSet(Pid_e steerPid, uint8 steerPidChange);//�趨���pid����

SteerTurnDirection_e SteerDirectionSetByAdcOne(struct FLAdc_s adc_s);

#endif//_FL_STEER_
