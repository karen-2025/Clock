#include "Mode.h"

 u8 LEDLightTemp;             // 数码管亮度 暂存
 bit RTCTimeDisplay_Bit = 1;  // 显示RTC时间 标志位
 bit Bit_125ms = 0;           // 1/8S 中断标志位
 
 u8 numtime_adjust = 0 ;      // 时间数值调整 加
 u8 Modenum = 0;              // 模式0 ，初始化设置为0
 u8 mus=0;
 bit Modenum1_bit = 0;        // 模式1 标志位
 bit Modenum2_bit = 0;        // 模式2 标志位
 bit Modenum3_bit = 0;        // 模式3 标志位
 bit Modenum4_bit = 0;        // 模式4 标志位
 bit Modenum5_bit = 0;        // 模式5 标志位
 bit Modenum7_bit = 0;        // 模式7 标志位
  
/********************************************************************************/	

 // 模式 1，按 EN 键进入设置，按 +，— 调节亮度，按 SET 键直接保存并返回模式界面		
void Mode_1()
{
	if(Keynum == 2)
	{
	 Modenum1_bit = 1;        // 模式1 标志位
	 ShowValue_A(37,38,30,Modenum,31,31,36,39);   // 显示 SE—1  ON	
	 ShowValue_B(31,31,31,31,31,31);    			 
	}

	if(Modenum1_bit == 1)
	{
		switch(Keynum)
		{
			case 3: 
				if(LEDCTRL >= 0x80&&LEDCTRL < 0x87)					 
					{
						LEDCTRL++;
						if(LEDCTRL == 0x87)
						 LEDCTRL = 0x87;
					}
			break;		
			case 1: 
				if(LEDCTRL > 0x80&&LEDCTRL <= 0x87)					 
					{ 
						LEDCTRL--;
						if(LEDCTRL == 0x80)
						 LEDCTRL = 0x80;
					}
			break;	
			default: break;				
		}
	}	
}
/********************************************************************************/	

// 模式 2，按 EN 键选择需要调节的时间，按 + — 键 调节数值，按 SET键直接保存并返回模式界面		
void Mode_2()
{
	Mode_TimeAdjust();
}   
/********************************************************************************/		

 // 模式 3，按 EN 键进入闹钟调节界面，按 SET 键退出并返回模式界面		 
void Mode_3()
{
  Mode_Clock();
}	
/********************************************************************************/							 

// 模式 4 ，按 EN 键进入温度显示界面，按 SET 键退出并返回模式界面	
void Mode_4()		
{
 if(Keynum == 2)
 {
	 Modenum4_bit = 1;        // 模式4 标志位		 
 }
}
/********************************************************************************/	

// 模式 5，按 EN 键进入 电量显示界面，按 SET 键退出并返回模式界面
void Mode_5()		
{
 if(Keynum == 2)
 {
	 	Modenum5_bit = 1; 
 }
}
/********************************************************************************/	

 // 模式 6，按 EN 键 缓慢息屏，按 SET键退出息屏状态，进入模式界面	
 void Mode_6()
{
	if(Keynum == 2)   
		{					 
			LEDLightTemp = LEDCTRL;   // 存取息屏前的 亮度值					 
			for(LEDCTRL=0x80;LEDCTRL<0x87;LEDCTRL++)  // 缓慢息屏
				delay_ms(30);	
			Show_Empty();	 	           // 息屏
			LEDCTRL = LEDLightTemp;		 // 恢复息屏前的 亮度值，确保下次点亮屏幕和息屏前亮度一致
		}
} 

// 模式 7，按 EN 键进入，按 +，— 选择播放的语音，按 SET 键直接返回模式界面		
void Mode_7()
{
	if(Keynum == 2)
	{
	 Modenum7_bit = 1;        // 模式7 标志位
	 ShowValue_A(37,38,30,Modenum,31,31,36,39);   // 显示 SE—7  ON	
	 ShowValue_B(31,31,31,31,31,31);    			 
	}

	if(Modenum7_bit == 1)
	{
		switch(Keynum)
		{
			case 1: 
				if(mus >= 0x00&&mus < 0x32 )
				{
					mus++;
					if(mus == 0x32)
					mus = 0x32;
				 	NV080C_Play(mus);
				}			
			break;		
			case 3: 
				if(mus > 0x00&&mus <= 0x32 )
				{
					mus--;
					if(mus == 0x00)
					mus = 0x00;
						NV080C_Play(mus);	
				}	
			break;	
			default: break;				
		}
	}	
}
/********************************************************************************/		


u8	isr_index;
void	AUXR_ISR(void) interrupt 13
{
	u8	j,i;	
	switch(isr_index)
	{
		case 32:		//0103H 波形发生器5 中断入口						
		break;     //用户中断处理代码
		case 33:		//010BH	波形发生器异常2 中断入口						
		break;     //用户中断处理代码
		case 34:		//0113H	波形发生器异常4 中断入口					
		break;      //用户中断处理代码
		case 35:		//011BH	触摸按键 中断入口
						   //用户中断处理代码
		j = TSSTA2;

		if(j & 0x40)	    //数据溢出, 错误处理(略)
		{
			TSSTA2 |= 0x40;	//写1清零
		}
		if(j & 0x80)	    //扫描完成
		{
			j &= 0x0f;
			TSSTA2 |= 0x80;	//写1清零	
			TK_cnt[j] = TSDAT;	//保存某个通道的读数	低通滤波
			if(j == 3)	
				B_ReadKeyOk = 1;	        //读完一次循环
		}
		break;
			
		case 36:		//0123H	RTC 中断入口
			i = RTCIF;
			RTCIF = 0;		//中断标志,0x80:闹钟中断,0x40:日中断, 0x20:小时中断, 0x10:分钟中断, 0x08:秒中断,
			if(i & 0x02)	//1/8秒中断,闪烁需要调节的时间点
			{
				Bit_125ms = ~ Bit_125ms ;  // 1/8 秒时间到，标志位反转
    // 以下是 时间调节界面闪烁				
				if(Modenum2_bit == 1)
				{				
					if(Bit_125ms == 0)
					{
						 switch(numtime_adjust) 
						 {
							 case 0: Display_Day(1 , RTC_YEAR%10);     break;
							 case 1: Display_Day(4 , RTC_MONTH%10);    break;
							 case 2: Display_Day(7 , RTC_DAY%10);      break;
							 case 3: Display_Time(1 , RTC_HOUR%10+10); break;
							 case 4: Display_Time(3 , RTC_MIN%10+10);  break;
							 case 5: Display_Time(5 , RTC_SEC%10);	   break;
							 default: break;
						 }											
					}
					else 
					{
			      switch(numtime_adjust) 
						 {
							 case 0: Display_Day(1 , 31);  break;
							 case 1: Display_Day(4 , 31);  break;
							 case 2: Display_Day(7 , 31);  break;
							 case 3: Display_Time(1 , 31); break;
							 case 4: Display_Time(3 , 31); break;
							 case 5: Display_Time(5 , 31); break;
							 default: break;
						 }	 
					}	 
			  }

//以下是 闹钟界面闪烁				
			if(Modenum3_bit == 1)
				{				
					if(Bit_125ms == 0)
					{
						 switch(numclock_adjust) 
						 {
							 case 1: Display_Day(7 , ClockENBit);	          break;
							 case 2: Display_Time(1 , Clock_1[0]%10+10);    break;
							 case 3: Display_Time(3 , Clock_1[1]%10+10);    break;
							 case 4: Display_Time(5 , Clock_1[2]%10);       break;
							 default: break;
						 }											
					}
					else 
					{
			      switch(numclock_adjust) 
						 {
							 case 1: Display_Day(7 , 31);	    break;
							 case 2: Display_Time(1 , 31);    break;
							 case 3: Display_Time(3 , 31);    break;
							 case 4: Display_Time(5 , 31);    break;
							 default: break;
						 }	 
					}	 
			  }				
/********************************************************************************/	
		  }				
		break;      //用户中断处理代码
		
		default:
		break;
	}
}


 
