#include "common.h"
#include "include.h"
#include "fl_include.h"



/************************************************************************/
/*                                 ���ܿ���                             */
/************************************************************************/
#define UseAdcNormalizingInit		DoNotUseIt//������һ��ʹ��
#define UseEndLine					DoNotUseIt//�յ���
#define UsePowerOnDelay				UseIt//������ʱ
#define UseEeprom					DoNotUseIt//���ô洢
#define UseLostRoadStop				UseIt//����ֹͣ
#define UseMpu6050ChangeSpeed		DoNotUseIt//�����ǿ���
#define UseDistanceChangeSpeed		DoNotUseIt//�������
#define UseSoundSpeedByTemperature	DoNotUseIt//�������¶Ȳ���
#define UseNrfSendOrReceiveMsg		UseIt
#define UseCar2NrfSendDistance		UseIt
#define UseCar1NrfSendAdc			UseIt

#define SpeedForTest				700//�����ٶ�

#define Car1						1
#define Car2						2
#define Car							Car1

