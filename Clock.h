#ifndef __CLOCK_H
#define __CLOCK_H

#include "STC8H4K64TL.h"
#include "Mode.h"

extern u8 numclock_adjust;          // 闹钟数据调整 加 
extern u8 ClockENBit ;          // 闹钟使能显示 N或 F，初始设置为F
extern u8 Clock1 ;
extern u8 Clock_1[];
extern bit Clock1_EN ;

void Mode_Clock();
void ClockTimeAdjust_Display();
void Clock1_Sound();

#endif

	