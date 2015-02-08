
#include "common.h"
#include "fl_messageshow.h"



char msg[MsgMaxLength];//存储消息文本

/************************************************************************/
/* 打印数据自带换行的哈:)                                   20150107    */
/************************************************************************/
void MessageShow(uint8 * str)
{
	sprintf(msg, "%s\r\n",str);
	printf(msg);
}

/************************************************************************/
/*  指示一下函数位置                                                    */
/*         仅debug模式有效                             20150107         */
/************************************************************************/
void FuncLocalShow(uint8 * str)
{
#if ( defined( DEBUG ) && defined( DEBUG_PRINT ))
	sprintf(msg, "This is the Func -> %s", str);
	MessageShow((uint8*)msg);
#endif
}
