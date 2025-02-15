
#ifndef __MODE_H
#define __MODE_H

#include "STC8H4K64TL.h"
#include "RTC.h"
#include "Display.h"
#include "Touch.h"
#include "Temperature.h"
#include "Time.h"
#include "Clock.h"
#include "Sound.h"


extern u8 LEDLightTemp;             // 数码管亮度 暂存
extern bit RTCTimeDisplay_Bit ;     // 显示RTC时间 标志位
extern bit Bit_125ms ;              // 1/8S 中断标志位
extern u8 numtime_adjust ;          // 时间加
extern u8 Modenum ;                 // 模式0 ，初始化设置为0
extern bit Modenum1_bit;            // 模式1 标志位
extern bit Modenum2_bit;            // 模式2 标志位
extern bit Modenum3_bit;            // 模式3 标志位
extern bit Modenum4_bit;            // 模式4 标志位
extern bit Modenum5_bit;            // 模式5 标志位
extern bit Modenum7_bit;            // 模式7 标志位
extern u8 numclock_adjust;          // 闹钟数据调整 加

void Mode_1();
void Mode_2();
void Mode_3();
void Mode_4();
void Mode_5();
void Mode_6();
void Mode_7();
void Clock1_Mode();

#endif

