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
#define UseNrfSendOrReceiveMsg		DoNotUseIt//nrfʹ��
#define UseCar2NrfSendDistance		DoNotUseIt//���봫��
#define UseCar1NrfSendAdc			DoNotUseIt//ad����
#define UseSteerDynamicFuzzyDomain	UseIt//�����̬����

#define SpeedForTest				1000//�����ٶ�

#define Car1						1
#define Car2						2
#define Car							Car1

