
#include "common.h"
#include "fl_messageshow.h"



char msg[MsgMaxLength];//�洢��Ϣ�ı�

/************************************************************************/
/* ��ӡ�����Դ����еĹ�:)                                   20150107    */
/************************************************************************/
void MessageShow(uint8 * str)
{
	sprintf(msg, "%s\r\n",str);
	printf(msg);
}

/************************************************************************/
/*  ָʾһ�º���λ��                                                    */
/*         ��debugģʽ��Ч                             20150107         */
/************************************************************************/
void FuncLocalShow(uint8 * str)
{
#if ( defined( DEBUG ) && defined( DEBUG_PRINT ))
	sprintf(msg, "This is the Func -> %s", str);
	MessageShow((uint8*)msg);
#endif
}
