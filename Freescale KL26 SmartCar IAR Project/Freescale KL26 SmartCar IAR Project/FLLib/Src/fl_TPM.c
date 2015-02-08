
#include "common.h"
#include "fl_tpm.h"

#ifdef MKL26Z4
#include "MKL_tpm.h"
#elif MK60F15
#include "MK60_tpm.h"
#elif MK60DZ10
#include "MK60_tpm.h"
#endif


uint16 count;//�������������ֵ

/************************************************************************/
/*   �����������������ֵ                          20150107             */
/************************************************************************/
uint16 TpmCountRead()
{
	FuncLocalShow("TpmCountRead");
	count = tpm_input_get (TPM2, TPM_CH0);
	printf("%d\r\n", count);
	tpm_input_clean(TPM2);                                  //����������������ֵ����ʼ�µļ�����
	return count;
}

/************************************************************************/
/* tpm��ʼ��                                           20150107         */
/*                                                                      */
/*     ���tpm0  400KHz                                                 */
/*     ���tpm1  400KHz                                                 */
/*     ������tpm2                                                       */
/************************************************************************/
void TpmInit()
{
	FuncLocalShow("TpmInit");
	tpm_pwm_init(TPM0, TPM_CH0, TpmMotorFreq, TmpPwmDutyDefault);//���
	//tpm_pwm_init(TPM1, TPM_CH0, TpmSteEngFreq, TmpPwmDutyDefault);//���
	//������Ҫ���о�һ��
	//tpm_pulse_init(TPM2, TPM_CLKIN0, TPM_PS_1); //��ʼ�� TPM2 Ϊ�����ۼӣ�����ܽ�Ϊ TPM_CLKIN0_PIN ����Ƶϵ��Ϊ 1
	tpm_input_init (TPM2, TPM_CH0,TPM_Rising, TPM_PS_2);
}
