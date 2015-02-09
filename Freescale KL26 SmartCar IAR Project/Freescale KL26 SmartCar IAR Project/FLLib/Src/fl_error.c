#include "fl_error.h"




LcdErr_e ConvertSettingerrTOLcderr(SettingErr_e settingErr)//´íÎóÀàĞÍ×ª»»
{
	switch (settingErr)
	{
	case SettingErrOverMax:
		return LcdErrOverMax;
		break;

	case SettingErrOverMin:
		return LcdErrOverMin;
		break;

	case SettingErrItemNotFound:
		return LcdErrOther;
		break;

	default:
		return LcdErrOther;
		break;
	}
}