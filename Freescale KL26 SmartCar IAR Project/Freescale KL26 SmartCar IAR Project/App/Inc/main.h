#include "common.h"
#include "include.h"
#include "fl_include.h"

uint8 buff[DATA_PACKET];


/************************************************************************/
/*                                 ���ܿ���                             */
/************************************************************************/
#define UseAdcNormalizingInit		DoNotUseIt//������һ��ʹ��
#define UseEndLine					DoNotUseIt
#define UsePowerOnDelay				UseIt
#define UseEeprom					DoNotUseIt
#define UseLostRoadStop				UseIt
#define UseMpu6050ChangeSpeed		DoNotUseIt

#define SpeedForTest				700

#define UseDistanceChangeSpeed		DoNotUseIt

#define Car1						1
#define Car2						2
#define Car							Car1

