#include "common.h"
#include "fl_cfg.h"
#include "Fl_steer.h"

#ifndef _FL_SteerFuzzy_
#define _FL_SteerFuzzy_

/*���Ա���ָ��*/
//���ƫ��仯��Χmax = 63
//����ǰƫ�����ֵmax=44
//
//ģ��������ƫ�Χ-6~6
#define SteerOffSetSum 13
//�ο�������������ǰ�ֵ�˼�룬�ݶ�7��
#define SteerGears 7
//#warning �����ڲ�ͬ�������ǲ�ͬ�ģ�����ʱ��Ҫɨ�裬�������ƹ�һ������
//ƫ������
#define OffSetMax	59
//ԭ������ֵ
#define ZeroPointUp (OffSetMax + 1)
//ƫ��仯������
#define ErrorChangeSpeedMax	6


extern uint16 SpeedForline;



void SteerVagueCtrl(int16 offset);
void SteerFuzzyDomainScan();


#endif//_FL_SteerFuzzy_
