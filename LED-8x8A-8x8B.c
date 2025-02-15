#include "STC8H4K64TL.h"
#include "RTC.h"
#include "Display.h"
#include "Touch.h"
#include "Mode.h"
#include "Beep.h"
#include "Uart.h"
#include "Clock.h"
#include "Time.h"
#include "Adc.h"

//----------------时钟设置为11.0592M-----------------------
void main()
{
	u8	i;
	Io_Init();           // IO端口初始化  
	UART1_config(MAIN_Fosc,19200);  // 请注意下载程序时使用的波特率 和 串口打印波特率设置要一致
	Beep_Init();         //蜂鸣器初始化
	Display_Init();      //屏幕显示初始化
	RTC_Init();	         //RTC初始化
	BatteryAdc_Init();   //电量显示初始化
	
	for(i=0; i<5; i++)              //开机动画
	{
		Display_Day(i , i+32) ;		   // 显示 HELLO
		Display_Time(i , 31);        // 第二排数码管不显示		
	}		
  Delay3000ms();                //开机动画 3S 时间
	
	Touch_Init();        //触摸按键初始化    
	
	while (1)
	{		
	  TouchKey_Value();             // 触摸按键循环检测
		RTCTime_Display();            // 时间显示 界面
		RTCTimeAdjust_Display();      // 时间调节 界面		
		ClockTimeAdjust_Display();    // 闹钟调节 界面
		CurrentTemperature_Display(); // 温度显示 界面
	  Clock1_Sound();               // 闹钟 响
	}
}




