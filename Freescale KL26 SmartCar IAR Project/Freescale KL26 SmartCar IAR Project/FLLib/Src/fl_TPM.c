
#include "common.h"
#include "fl_tpm.h"

#ifdef MKL26Z4
#include "MKL_tpm.h"
#elif MK60F15
#include "MK60_tpm.h"
#elif MK60DZ10
#include "MK60_tpm.h"
#endif


uint16 count;//脉冲计数器计算值

/************************************************************************/
/*   保存脉冲计数器计算值                          20150107             */
/************************************************************************/
uint16 TpmCountRead()
{
	FuncLocalShow("TpmCountRead");
	count = tpm_input_get (TPM2, TPM_CH0);
	printf("%d\r\n", count);
	tpm_input_clean(TPM2);                                  //清空脉冲计数器计算值（开始新的计数）
	return count;
}

/************************************************************************/
/* tpm初始化                                           20150107         */
/*                                                                      */
/*     电机tpm0  400KHz                                                 */
/*     舵机tpm1  400KHz                                                 */
/*     编码器tpm2                                                       */
/************************************************************************/
void TpmInit()
{
	FuncLocalShow("TpmInit");
	tpm_pwm_init(TPM0, TPM_CH0, TpmMotorFreq, TmpPwmDutyDefault);//电机
	//tpm_pwm_init(TPM1, TPM_CH0, TpmSteEngFreq, TmpPwmDutyDefault);//舵机
	//计数还要再研究一下
	//tpm_pulse_init(TPM2, TPM_CLKIN0, TPM_PS_1); //初始化 TPM2 为脉冲累加，输入管脚为 TPM_CLKIN0_PIN ，分频系数为 1
	tpm_input_init (TPM2, TPM_CH0,TPM_Rising, TPM_PS_2);
}
