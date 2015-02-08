
#include "common.h"
#include "fl_coder.h"
#include "fl_olcd.h"
#include "fl_bluetooth.h"
#include "MKL_tpm.h"

uint16 moterExpect = 0;
uint16 moterActually = 0;
char CoderStr []= "\0";

void CoderRead()
{
	FuncLocalShow("CoderRead");

	moterActually = tpm_pulse_get(TpmCoder);
    tpm_pulse_clean(TPM2); 
}

void CoderShow()
{FuncLocalShow("CoderShow");
	NumShow(moterExpect, MoterExpectX, MoterExpectY);
	NumShow(moterActually, MoterActuallyX, MoterActuallyY);

	/*
	sprintf(CoderStr, "%d", moterExpect);
	LCD_P8x16Str(MoterExpectX, MoterExpectY, CoderStr);
	sprintf(CoderStr, "%d", moterActually);
	LCD_P8x16Str(MoterActuallyX, MoterActuallyY, CoderStr);*/
}

void CoderShowAutoRead()
{
	CoderRead();
	CoderShow();
}

void CoderBlueToothSend()
{
	sprintf(CoderStr, "$moterExpect:%d\r\n$moterActualy:%d\r\n", moterExpect, moterActually);
	BlueToothShow(CoderStr);
}

void CoderBlueToothSendAutoRead()
{
	CoderRead();
	CoderBlueToothSend();
}

void CoderUartSend()
{
	printf("$moterExpect:%d\r\n$moterActualy:%d\r\n", moterExpect, moterActually);
}

void CoderUartSendAutoRead()
{
	CoderRead();
	CoderUartSend();
}

