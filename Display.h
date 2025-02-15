#ifndef __Display_H
#define __Display_H

#include "STC8H4K64TL.h"
void Io_Init();
void Display_Init();
void Display_Day(u8 num , u8 dat);
void Display_Time(u8 num , u8 dat);
void Display_CurrentTime();
void Show_Empty();
void ShowValue_A(u8 chn0,u8 chn1,u8 chn2,u8 chn3,u8 chn4,u8 chn5,u8 chn6,u8 chn7);
void ShowValue_B(u8 chn0,u8 chn1,u8 chn2,u8 chn3,u8 chn4,u8 chn5);

#endif

