#include "common.h"
#include "fl_cfg.h"

#ifndef  _FL_ERROR_
#define _FL_ERROR_

//////////////////////////////////////////////////////////////////////////
typedef enum
{
	SettingAllGreen,//正常

	SettingErrOverMax,//超过最大值
	SettingErrOverMin,//超过最小值

	SettingErrItemNotFound,//404

	SettingErrOther,//未定义错误

	SettingErrNumbers,//错误总数
}SettingErr_e;//错误号

//////////////////////////////////////////////////////////////////////////
typedef enum
{
	LcdErrOverMax,//超过最大值
	LcdErrOverMin,//超过最小值

	LcdErrKeyWrong,//当前界面不支持该按键

	LcdErrOther,//未定义错误

	LcdErrNumbers,//错误总数
}LcdErr_e;//错误号


LcdErr_e ConvertSettingerrTOLcderr(SettingErr_e settingErr);
#endif
