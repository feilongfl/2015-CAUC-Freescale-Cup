
#ifndef _FL_INIT_
#define _FL_INIT_





typedef enum 
{
	InitAllGreen,
	InitFailed,
}InitRepot_e;//初始化状态




/************************************************************************/
/*                            初始化                                    */
/*                                                                      */
/*                                                                      */
/*     你需要在使用所有模块之前调用此函数。                             */
/*                                                  20150107            */
/************************************************************************/
InitRepot_e Init();
#endif //_FL_INIT_


