#include "RTC.h"


void RTC_Init()      // RTC初始化配置
{
	P_SW2 |= 0x80;	    //使能 XFR 访问	
	//IRC32KCR = 0x80;            // 内部32K晶振受工作电压和环境温度影响极大，误差很大，不使用内部晶振
  //while(!(IRC32KCR & 0x01));  // 等待时钟稳定
  //RTCCFG = 0x02;	            // 选择内部 32K 作为时钟源
	
  P1IE = ~0xc0;				//P1.6 P1.7关闭数字输入功能
	X32KCR = 0x80 + 0x40;   //启动外部32K晶振, 低增益+0x00, 高增益+0x40.
	while(!(X32KCR & 0x01));   // 等待时钟稳定	
	RTCCFG = 0x00;    //选择外部32K时钟源，触发RTC寄存器初始化
	
	INIYEAR = 23;    // 初始化赋时间，23年 08月 30日 12时 30分 00秒 
	INIMONTH = 8;
	INIDAY = 30;
	INIHOUR = 12;
	INIMIN = 30;
	INISEC = 00;	
	INISSEC = 00;	    // 128分之//一 秒
  RTCCFG |= 0x01;    // 将 初始时间赋值到 RTC中

	RTCIF   = 0x00;	//清中断标志
	RTCIEN  = 0x02;	//中断使能, 0x80:闹钟中断, 0x40:日中断, 0x20:小时中断, 0x10:分钟中断, 0x08:秒中断, 0x04:1/2秒中断, 0x02:1/8秒中断, 0x01:1/32秒中断
	RTCCR = 0x01;     //RTC使能
}
