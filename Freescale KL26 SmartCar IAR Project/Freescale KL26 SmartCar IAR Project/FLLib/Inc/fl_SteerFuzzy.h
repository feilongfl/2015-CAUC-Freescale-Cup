#include "common.h"
#include "fl_cfg.h"
#include "Fl_steer.h"

#ifndef _FL_SteerFuzzy_
#define _FL_SteerFuzzy_

/*语言变量指表*/
//电感偏差变化范围max = 63
//丢线前偏差最大值max=44
//
//模糊化控制偏差范围-6~6
#define SteerOffSetSum 13
//参考其他方案和以前分档思想，暂定7档
#define SteerGears 7
//#warning 论域在不同环境下是不同的，开机时需要扫描，进行类似归一化处理
//偏差论域
#define OffSetMax	59
//原点提升值
#define ZeroPointUp (OffSetMax + 1)
//偏差变化率论域
#define ErrorChangeSpeedMax	6


extern uint16 SpeedForline;



void SteerVagueCtrl(int16 offset);
void SteerFuzzyDomainScan();


#endif//_FL_SteerFuzzy_
