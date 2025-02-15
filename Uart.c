#include "Uart.h"

bit B_TX1_Busy;

//UART1初始化函数。
void	UART1_config(u32 clk, u32 brt)
{
	brt = 65536UL - (clk / 4) / brt;
	TR1 = 0;
	AUXR &= ~0x01;		//S1 BRT Use Timer1;
	AUXR |=  (1<<6);	//Timer1 set as 1T mode
	TMOD &= ~(1<<6);	//Timer1 set As Timer
	TMOD &= ~0x30;		//Timer1_16bitAutoReload;
	TH1 = (u8)(brt >> 8);
	TL1 = (u8)brt;
	ET1 = 0;			// 禁止Timer1中断
	INTCLKO &= ~0x02;	// Timer1不输出高速时钟
	TR1  = 1;			// 运行Timer1

	P_SW1 &= 0x3f;
	P_SW1 |= 0x00;      //UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7, 0xC0: P4.3 P4.4

	SCON = (SCON & 0x3f) | (1<<6);	// 8位数据, 1位起始位, 1位停止位, 无校验
	PS  = 1;	//高优先级中断
	ES  = 1;	//允许中断
	REN = 1;	//允许接收

	B_TX1_Busy = 0;
}
/********************************************************************************/

u8 code *STCISPCMD = "@STCISP#";   
u8 code *STCRTC  = "@STCRTC#";  //= "@STCRTC#";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 B#";

u8 index=0;
u8 indexrtc=0;
u8 length =0;
u8 xdata rtctime[12] = 0;
bit  Rec_OK = 0;
/********************************************************************************/

//串口1中断函数
void UART1_int (void) interrupt 4
{
   u8 dat;
	 if(RI)
	  {
		   RI = 0;
       dat = SBUF;
//ISP不停电下载    
       if (dat == STCISPCMD[index])
        {
					index++;
					if(STCISPCMD[index] == '\0')
					{
						EA =0;                       //强制禁用中断，防止打断升级
						IAP_CONTR=0x60;
					}
        }
        else
        {
					index = 0;
					if (dat == STCISPCMD[index])
					index++;
        }
/********************************************************************************/

//串口RTC对时
        if( length>0 )
        {     
					rtctime[length-1] = dat;
					length++;
					if(length >= 12)
					{
						length = 0;
						Rec_OK = 1;
						indexrtc=0;
					}
        }        
        if (dat == STCRTC[indexrtc])
        {
					indexrtc++;
					if(STCRTC[indexrtc] == '\0')
					{
						length = 1;   //开启接收
						indexrtc=0;
					}
        }
        else
        {
					indexrtc = 0;
					if (dat == STCRTC[indexrtc])
					indexrtc++;
        }  
	}
/********************************************************************************/
		
 // 通过串口获取当前时间，赋给 RTC 		
			if(Rec_OK == 1)             
		{			
			Rec_OK = 0;
			RTCCR = 0;                      //上传当前的RTC值时,必须临时停止RTC,以免发生进位错误
			INIYEAR = rtctime[1];                 
			INIMONTH = rtctime[2];
			INIDAY = rtctime[3];
			INIHOUR = rtctime[5];
			INIMIN = rtctime[6];
			INISEC = rtctime[7];	
			INISSEC = rtctime[8];	  
			RTCCR = 1;                     
			RTCCFG |= 0x01;                   			
		}

	if(TI)
	{
		TI = 0;
		B_TX1_Busy = 0;
	}
}


