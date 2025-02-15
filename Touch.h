#ifndef __TOUCH_H
#define __TOUCH_H

#include "STC8H4K64TL.h"
#include "RTC.h"
#include "Display.h"
#include "Touch.h"
#include "Temperature.h"
#include "Mode.h"
#include "Beep.h"
#include "Sound.h"
#define MAIN_Fosc	11059200L	//定义主时钟

//本地变量声明	
extern u16	xdata TK_cnt[4];	  // 键计数值
extern u16	xdata TK_zero[4];	  // 0点读数 
extern u16	KeyState;		        //键状态
extern u8	Keynum;		          //键码 1-6
extern bit	B_ReadKeyOk;	      //标志已转换完成5个键
extern u8	TrigLimit;		      //触发转换限时 
extern u8 i;
extern u16 code T_KeyState[4];
extern u16 code T_KeyPress[4];
extern u16	j;


void  Touch_Init();
void  delay_ms(u8 ms);
u8		CheckKey(u16 j);
void  delay_ms(u8 ms);
void Delay3000ms();
void TouchKey_Value();

#endif

