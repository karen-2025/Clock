#include "Clock.h"

 u8 numclock_adjust = 1;           // 闹钟数据调整 加 
 u8 ClockENBit = 40 ;          // 闹钟使能显示 N或 F，初始设置为F
 u8 Clock1 = 1;                // 闹钟 1
 u8 Clock_1[] = {0x08,0x00,0x00};  // 闹钟1 初始设置时间
 bit Clock1_EN = 0;                // 闹钟1 使能标志位
 
//闹钟 调节
void Mode_Clock()
{
	if(Keynum == 2)
	{
		Modenum3_bit = 1;        // 模式3 标志位
		numclock_adjust++;
		if(numclock_adjust > 4)
			numclock_adjust = 1;		
	}
	
	if(Keynum == 1)
	{
		switch(numclock_adjust)                     
		{ 
			case 1: ClockENBit = 39;Clock1_EN = 1;break; 			
			case 2: if(Clock_1[0] >=0 && Clock_1[0] < 23) Clock_1[0]++;if(Clock_1[0] == 23) Clock_1[0] = 23;  break;   // 加  数值
			case 3: if(Clock_1[1] >=0 && Clock_1[1] < 59) Clock_1[1]++;if(Clock_1[1] == 59) Clock_1[1] = 59;  break;   // 加  数值
			case 4: if(Clock_1[2] >=0 && Clock_1[2] < 59) Clock_1[2]++;if(Clock_1[2] == 59) Clock_1[2] = 59;  break;   // 加  数值
			default: break;
		}
	}					

	if(Keynum == 3)
	{
		switch(numclock_adjust)
		{
			case 1: ClockENBit = 40;Clock1_EN = 0; break; 
			case 2: if(Clock_1[0] >0 && Clock_1[0] <= 23) Clock_1[0]--;if(Clock_1[0] == 0) Clock_1[0] = 0;  break;   // 减  数值
			case 3: if(Clock_1[1] >0 && Clock_1[1] <= 59) Clock_1[1]--;if(Clock_1[1] == 0) Clock_1[1] = 0;  break;   // 减  数值
			case 4: if(Clock_1[2] >0 && Clock_1[2] <= 59) Clock_1[2]--;if(Clock_1[2] == 0) Clock_1[2] = 0;  break;   // 减  数值
			default: break;
	  }
  }
}
/********************************************************************************/	

// 显示 闹钟 调节界面，被调节位置 闪烁		
void ClockTimeAdjust_Display()
{

	
	if(Modenum3_bit == 1 && numclock_adjust == 1)
	{
		Display_Day(0 , 41);            
	  Display_Day(1 , 42);    
		Display_Day(2 , 30);               
		Display_Day(3 , Clock1);	 
		Display_Day(4 , 31);   
		Display_Day(5 , 31);           
		Display_Day(6 , 36);    
	//	Display_Day(7 , ClockENBit);	   
		
		Display_Time(0 , Clock_1[0]/10);	    
		Display_Time(1 , Clock_1[0]%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号 需要+10
		Display_Time(2 , Clock_1[1]/10);
		Display_Time(3 , Clock_1[1]%10+10);
		Display_Time(4 , Clock_1[2]/10);	
		Display_Time(5 , Clock_1[2]%10);		
	}	
	
	if(Modenum3_bit == 1 && numclock_adjust == 2)
	{
		Display_Day(0 , 41);            
	  Display_Day(1 , 42);    
		Display_Day(2 , 30);               
		Display_Day(3 , Clock1);	 
		Display_Day(4 , 31);   
		Display_Day(5 , 31);           
		Display_Day(6 , 36);    
		Display_Day(7 , ClockENBit);	   
		
		Display_Time(0 , Clock_1[0]/10);	    
		//Display_Time(1 , Clock_1[0]%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号 需要+10
		Display_Time(2 , Clock_1[1]/10);
		Display_Time(3 , Clock_1[1]%10+10);
		Display_Time(4 , Clock_1[2]/10);	
		Display_Time(5 , Clock_1[2]%10);	
	}	
	
	if(Modenum3_bit == 1 && numclock_adjust == 3)
	{
		Display_Day(0 , 41);            
	  Display_Day(1 , 42);    
		Display_Day(2 , 30);               
		Display_Day(3 , Clock1);	 
		Display_Day(4 , 31);   
		Display_Day(5 , 31);           
		Display_Day(6 , 36);    
		Display_Day(7 , ClockENBit);	   
		
		Display_Time(0 , Clock_1[0]/10);	    
		Display_Time(1 , Clock_1[0]%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号 需要+10
		Display_Time(2 , Clock_1[1]/10);
		//Display_Time(3 , Clock_1[1]%10+10);
		Display_Time(4 , Clock_1[2]/10);	
		Display_Time(5 , Clock_1[2]%10);		
	}	
	
	if(Modenum3_bit == 1 && numclock_adjust == 4)
	{
		Display_Day(0 , 41);            
	  Display_Day(1 , 42);    
		Display_Day(2 , 30);               
		Display_Day(3 , Clock1);	 
		Display_Day(4 , 31);   
		Display_Day(5 , 31);           
		Display_Day(6 , 36);    
		Display_Day(7 , ClockENBit);	   
		
		Display_Time(0 , Clock_1[0]/10);	    
		Display_Time(1 , Clock_1[0]%10+10);   // 显示 第二行 第 1 个数码管，时，带冒号 需要+10
		Display_Time(2 , Clock_1[1]/10);
		Display_Time(3 , Clock_1[1]%10+10);
		Display_Time(4 , Clock_1[2]/10);	
		//Display_Time(5 , Clock_1[2]%10);		
	}	
}
/********************************************************************************/	

// 闹钟响
void Clock1_Sound()
{
	if(Clock1_EN ==1)
	{
		if(Clock_1[0] == RTC_HOUR && Clock_1[1] == RTC_MIN)
			{
       Beep_ClockSound();
			}
	}
}

/********************************************************************************/	