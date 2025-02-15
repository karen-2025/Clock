#include "Display.h"

//标准字库，共阴数码管
u8 code Display_SEG[]=					                             	
	{ 
		0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,        // 显示 0-9 
		0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,        // 显示 0-9，带冒号
	  0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,        // 显示 0-9, 带小数点 
		0x40,0x00,                                                // 显示 —，空 ;30开始
		0x76,0x79,0x38,0x38,0x3f,0x6d,0x79,0x37,0x71,0x39,0x38,0x3e    // 显示 H,E,L,L,O,S,E,N,F,C,L,U ;32开始
  };   
/********************************************************************************/	


void Io_Init()    // 单片机 IO口初始化配置
{
	P_SW2 |= 0x80;	//允许访问XSFR(扩展特殊功能寄存器)
	P0M0 = 0x0f;
	P0M1 = 0x20;   // P0.0-3 口连接 数码管 SEG8-11 端口，设置为 强推挽, P0.5 是ADC采集口，设置为高阻态，其余设置为准双向
	P1M0 = 0x00; 
	P1M1 = 0xdf;   // P1.5 为温度芯片，设置准双向口，其余设置为 高阻态,其中 P1.0,1,3.P5.4是触摸按键，P1.6 1.7连接外部晶振
	P2M0 = 0xff;
	P2M1 = 0x00;   // P2 口连接 数码管 COM0-7 共阴端口，设置为 强推挽
  P3M0 = 0xf0;
	P3M1 = 0x00;   // P3.4-7 口连接 数码管 SEG12-15 端口，设置为 强推挽,其余设置为准双向
	P4M0 = 0xff;   
	P4M1 = 0x00;   // P4 口连接 数码管 SEG1-7 端口，设置为强推挽	
	P5M0 = 0x08;   
	P5M1 = 0xf0;   // P5.3接LED，设置为强推挽，P5.2接蜂鸣器，设置为准双向，其余为高阻态
	
  P0DR &= ~0x0f;  // 设置强电流模式
  P2DR = 0x00;    // 设置强电流模式
	P3DR &= ~0xf0;  // 设置强电流模式

}

void Display_Init()   //LED 驱动相关寄存器配置
{
	P_SW2 |= 0x80;	 //允许访问XSFR(扩展特殊功能寄存器)
	COMEN = 0xff;    // COM0-7 端口使能
	SEGENL = 0xff;   // SEG 0-7 端口使能
	SEGENH = 0xff;   // SEG 8-15 端口使能
	LEDCTRL =0x80;   // LED 驱动，共阴模式,亮度为000最大
	LEDCKS = 7;      // 设置LED刷新频率为 7
}


void Display_Day(u8 num , u8 dat)   // 显示第一行数码管，即 年月日，num 表示第几个数码管，dat 表示数据
{
	switch(num)
	{
		case 0:  COM7_DCL = Display_SEG[dat]; break;
		case 1:  COM6_DCL = Display_SEG[dat]; break;
		case 2:  COM5_DCL = Display_SEG[dat]; break;     
		case 3:  COM4_DCL = Display_SEG[dat]; break;
		case 4:  COM3_DCL = Display_SEG[dat]; break;
		case 5:  COM2_DCL = Display_SEG[dat]; break;     
		case 6:  COM1_DCL = Display_SEG[dat]; break;
		case 7:  COM0_DCL = Display_SEG[dat]; break;
		default:break;	
	}	
}	

void Display_Time(u8 num , u8 dat)     // 显示第二行 数码管，即 时分秒，num 表示第几个数码管，dat 表示数据
{	
	switch(num)
	{
		case 0:  COM5_DCH = Display_SEG[dat]; break;
		case 1:  COM4_DCH = Display_SEG[dat]; break;      //显示时间需要带冒号
		case 2:  COM3_DCH = Display_SEG[dat]; break;
		case 3:  COM2_DCH = Display_SEG[dat]; break;      //显示时间需要带冒号
		case 4:  COM1_DCH = Display_SEG[dat]; break;
		case 5:  COM0_DCH = Display_SEG[dat]; break;
		default:break;	
	}
}	

/********************************************************************************/
void Display_CurrentTime()              //  显示 RTC 时间
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
		Display_Time(5 , RTC_SEC%10);		
}

void	ShowValue_A(u8 chn0,u8 chn1,u8 chn2,u8 chn3,u8 chn4,u8 chn5,u8 chn6,u8 chn7)  // 显示 第一行 数码管
{
	Display_Day(0 , chn0);       
	Display_Day(1 , chn1);    
	Display_Day(2 , chn2);        
	Display_Day(3 , chn3);	 
	Display_Day(4 , chn4);   
	Display_Day(5 , chn5);          
	Display_Day(6 , chn6);     
	Display_Day(7 , chn7);	   		
}

void	ShowValue_B(u8 chn0,u8 chn1,u8 chn2,u8 chn3,u8 chn4,u8 chn5) // 显示 第二行 数码管
{
	Display_Time(0 , chn0);	   
	Display_Time(1 , chn1);     
	Display_Time(2 , chn2);
	Display_Time(3 , chn3);
	Display_Time(4 , chn4);
	Display_Time(5 , chn5);	
}


void	Show_Empty()  //  清屏
{
  ShowValue_A(31,31,31,31,31,31,31,31);
	ShowValue_B(31,31,31,31,31,31);
}
	
