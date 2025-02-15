#ifndef __TEM_H
#define __TEM_H

#include "STC8H4K64TL.h"
#include "Display.h"
#include "Mode.h"

void delay(u16 i);
void Init_DS18B20(); 
u8 ReadOneChar();  			//主机数据线先从高拉至低电平1us以上，再使数据线升为高电平，从而产生读信号
void WriteOneChar(u8 dat); 
void ReadTemperature(); 
void Led(u16 date);
void CurrentTemperature_Display();

#endif

	