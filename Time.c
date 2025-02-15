#include "Time.h"

void	Mode_TimeAdjust()
{
	if(Keynum == 2)   
	 {	
			Modenum2_bit = 1;			                // 模式 2 标志位		 
			numtime_adjust++;
			if(numtime_adjust > 5)
				numtime_adjust = 0;	
	 }	

	if(Keynum == 1)
	{
	switch(numtime_adjust)                       //上传当前的RTC值时,必须临时停止RTC,以免发生进位错误
	{
	case 0: GetRtcTime();RTCCR = 0; if(INIYEAR >=0 && INIYEAR < 99) INIYEAR++;if(INIYEAR == 99)	INIYEAR = 99;       RTCCR = 1; RTCCFG |= 0x01; break;   // 加 年 数值
	case 1: GetRtcTime();RTCCR = 0; if(INIMONTH >=0 && INIMONTH < 12) INIMONTH++;if(INIMONTH == 12) INIMONTH = 12;  RTCCR = 1; RTCCFG |= 0x01; break;   // 加 月 数值
	case 2: GetRtcTime();RTCCR = 0; if(INIDAY >=0 && INIDAY < 31) INIDAY++;if(INIDAY == 31) INIDAY = 31;            RTCCR = 1; RTCCFG |= 0x01; break;   // 加 日 数值
	case 3: GetRtcTime();RTCCR = 0; if(INIHOUR >=0 && INIHOUR < 23) INIHOUR++;if(INIHOUR == 23) INIHOUR = 23;       RTCCR = 1; RTCCFG |= 0x01; break;   // 加 时 数值
	case 4: GetRtcTime();RTCCR = 0; if(INIMIN >=0 && INIMIN < 59) INIMIN++;	if(INIMIN == 59) INIMIN = 59;           RTCCR = 1; RTCCFG |= 0x01; break;   // 加 分 数值
	case 5: GetRtcTime();RTCCR = 0; if(INISEC >=0 && INISEC < 59) INISEC++;if(INISEC == 59) INISEC = 59;            RTCCR = 1; RTCCFG |= 0x01; break;   // 加 秒 数值
	}
	}					

	if(Keynum == 3)
	{
	switch(numtime_adjust)
	{
	case 0: GetRtcTime();RTCCR = 0; if(INIYEAR >0 && INIYEAR <= 99) INIYEAR--;if(INIYEAR == 0)	INIYEAR = 0;      RTCCR = 1; RTCCFG |= 0x01; break;   // 减 年 数值
	case 1: GetRtcTime();RTCCR = 0; if(INIMONTH >0 && INIMONTH <=12) INIMONTH--;if(INIMONTH == 0) INIMONTH = 0;   RTCCR = 1; RTCCFG |= 0x01; break;   // 减 月 数值
	case 2: GetRtcTime();RTCCR = 0; if(INIDAY >0 && INIDAY <= 31) INIDAY--;if(INIDAY == 0) INIDAY = 0;            RTCCR = 1; RTCCFG |= 0x01; break;   // 减 日 数值
	case 3: GetRtcTime();RTCCR = 0; if(INIHOUR >0 && INIHOUR <= 23) INIHOUR--;if(INIHOUR == 0) INIHOUR = 0;       RTCCR = 1; RTCCFG |= 0x01; break;   // 减 时 数值
	case 4: GetRtcTime();RTCCR = 0; if(INIMIN >0 && INIMIN <= 59) INIMIN--;	if(INIMIN == 0) INIMIN = 0;           RTCCR = 1; RTCCFG |= 0x01; break;   // 减 分 数值
	case 5: GetRtcTime();RTCCR = 0; if(INISEC >0 && INISEC <= 59) INISEC--;if(INISEC == 0) INISEC = 0;            RTCCR = 1; RTCCFG |= 0x01; break;   // 减 秒 数值
	}
	}
}



// 显示 RTC时间		
void RTCTime_Display()
{
		if(RTCTimeDisplay_Bit == 1&&Modenum == 0)
	{
		Display_CurrentTime();		
	}	
}

/********************************************************************************/	

// 显示 RTC 调节时间，被调节位置 闪烁		
void RTCTimeAdjust_Display()
{
	
		if(Modenum2_bit == 1 && numtime_adjust == 0)
	{

		Display_Day(0 , RTC_YEAR/10);       // 显示 第一行 第 0 个数码管，年
	//	Display_Day(1 , RTC_YEAR%10);    
		Display_Day(2 , 30);                // 显示 第一行 第 2 个数码管，——
		Display_Day(3 , RTC_MONTH/10);	 
		Display_Day(4 , RTC_MONTH%10);   
		Display_Day(5 , 30);           
		Display_Day(6 , RTC_DAY/10);    
		Display_Day(7 , RTC_DAY%10);	   
		
		Display_Time(0 , RTC_HOUR/10);	    // 显示 第二行 第 0 个数码管，时
		Display_Time(1 , RTC_HOUR%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号
		Display_Time(2 , RTC_MIN/10);
		Display_Time(3 , RTC_MIN%10+10);
		Display_Time(4 , RTC_SEC/10);	
		Display_Time(5 , RTC_SEC%10);		
	}	
		
			if(Modenum2_bit == 1 && numtime_adjust == 1)
	{
		Display_Day(0 , RTC_YEAR/10);       // 显示 第一行 第 0 个数码管，年
		Display_Day(1 , RTC_YEAR%10);    
		Display_Day(2 , 30);                // 显示 第一行 第 2 个数码管，——
		Display_Day(3 , RTC_MONTH/10);	 
		//Display_Day(4 , RTC_MONTH%10);   
		Display_Day(5 , 30);           
		Display_Day(6 , RTC_DAY/10);    
		Display_Day(7 , RTC_DAY%10);	   
		
		Display_Time(0 , RTC_HOUR/10);	    // 显示 第二行 第 0 个数码管，时
		Display_Time(1 , RTC_HOUR%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号
		Display_Time(2 , RTC_MIN/10);
		Display_Time(3 , RTC_MIN%10+10);
		Display_Time(4 , RTC_SEC/10);	
		Display_Time(5 , RTC_SEC%10);		
	}	
	
			if(Modenum2_bit == 1 && numtime_adjust == 2)
	{
		Display_Day(0 , RTC_YEAR/10);       // 显示 第一行 第 0 个数码管，年
	  Display_Day(1 , RTC_YEAR%10);    
		Display_Day(2 , 30);                // 显示 第一行 第 2 个数码管，——
		Display_Day(3 , RTC_MONTH/10);	 
		Display_Day(4 , RTC_MONTH%10);   
		Display_Day(5 , 30);           
		Display_Day(6 , RTC_DAY/10);    
		//Display_Day(7 , RTC_DAY%10);	   
		
		Display_Time(0 , RTC_HOUR/10);	    // 显示 第二行 第 0 个数码管，时
		Display_Time(1 , RTC_HOUR%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号
		Display_Time(2 , RTC_MIN/10);
		Display_Time(3 , RTC_MIN%10+10);
		Display_Time(4 , RTC_SEC/10);	
		Display_Time(5 , RTC_SEC%10);		
	}	
	
			if(Modenum2_bit == 1 && numtime_adjust == 3)
	{
		Display_Day(0 , RTC_YEAR/10);       // 显示 第一行 第 0 个数码管，年
		Display_Day(1 , RTC_YEAR%10);    
		Display_Day(2 , 30);                // 显示 第一行 第 2 个数码管，——
		Display_Day(3 , RTC_MONTH/10);	 
		Display_Day(4 , RTC_MONTH%10);   
		Display_Day(5 , 30);           
		Display_Day(6 , RTC_DAY/10);    
		Display_Day(7 , RTC_DAY%10);	   
		
		Display_Time(0 , RTC_HOUR/10);	    // 显示 第二行 第 0 个数码管，时
		//Display_Time(1 , RTC_HOUR%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号
		Display_Time(2 , RTC_MIN/10);
		Display_Time(3 , RTC_MIN%10+10);
		Display_Time(4 , RTC_SEC/10);	
		Display_Time(5 , RTC_SEC%10);		
	}	
	
			if(Modenum2_bit == 1 && numtime_adjust == 4)
	{
		Display_Day(0 , RTC_YEAR/10);       // 显示 第一行 第 0 个数码管，年
	  Display_Day(1 , RTC_YEAR%10);    
		Display_Day(2 , 30);                // 显示 第一行 第 2 个数码管，——
		Display_Day(3 , RTC_MONTH/10);	 
		Display_Day(4 , RTC_MONTH%10);   
		Display_Day(5 , 30);           
		Display_Day(6 , RTC_DAY/10);    
		Display_Day(7 , RTC_DAY%10);	   
		
		Display_Time(0 , RTC_HOUR/10);	    // 显示 第二行 第 0 个数码管，时
		Display_Time(1 , RTC_HOUR%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号
		Display_Time(2 , RTC_MIN/10);
		//Display_Time(3 , RTC_MIN%10+10);
		Display_Time(4 , RTC_SEC/10);	
		Display_Time(5 , RTC_SEC%10);		
	}	
	
			if(Modenum2_bit == 1 && numtime_adjust == 5)
	{
		Display_Day(0 , RTC_YEAR/10);       // 显示 第一行 第 0 个数码管，年
		Display_Day(1 , RTC_YEAR%10);    
		Display_Day(2 , 30);                // 显示 第一行 第 2 个数码管，——
		Display_Day(3 , RTC_MONTH/10);	 
		Display_Day(4 , RTC_MONTH%10);   
		Display_Day(5 , 30);           
		Display_Day(6 , RTC_DAY/10);    
		Display_Day(7 , RTC_DAY%10);	   
		
		Display_Time(0 , RTC_HOUR/10);	    // 显示 第二行 第 0 个数码管，时
		Display_Time(1 , RTC_HOUR%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号
		Display_Time(2 , RTC_MIN/10);
		Display_Time(3 , RTC_MIN%10+10);
		Display_Time(4 , RTC_SEC/10);	
		//Display_Time(5 , RTC_SEC%10);		
	}	
}
/********************************************************************************/	

void GetRtcTime()      // 从寄存器获取当前时间
{
	INIYEAR = RTC_YEAR;
	INIMONTH = RTC_MONTH;
	INIDAY = RTC_DAY;
	INIHOUR	= RTC_HOUR;				
	INIMIN = RTC_MIN;
	INISEC = RTC_SEC;	
}
/********************************************************************************/	