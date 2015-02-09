#include "common.h"
#include "fl_cfg.h"

#ifndef  _FL_ERROR_
#define _FL_ERROR_

//////////////////////////////////////////////////////////////////////////
typedef enum
{
	SettingAllGreen,//����

	SettingErrOverMax,//�������ֵ
	SettingErrOverMin,//������Сֵ

	SettingErrItemNotFound,//404

	SettingErrOther,//δ�������

	SettingErrNumbers,//��������
}SettingErr_e;//�����

//////////////////////////////////////////////////////////////////////////
typedef enum
{
	LcdErrOverMax,//�������ֵ
	LcdErrOverMin,//������Сֵ

	LcdErrKeyWrong,//��ǰ���治֧�ָð���

	LcdErrOther,//δ�������

	LcdErrNumbers,//��������
}LcdErr_e;//�����


LcdErr_e ConvertSettingerrTOLcderr(SettingErr_e settingErr);
#endif
