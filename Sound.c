#include "Sound.h"

sbit sda = P5^0;
u8 RTC_YEAR_Temp,RTC_MONTH_Temp,RTC_DAY_Temp,RTC_HOUR_Temp,RTC_MIN_Temp,RTC_SEC_Temp;

u8 code Voice_content[] = 
{ 
 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
 0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,
 0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,
 0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,
 0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32
};

void NV080C_Play(u8 addr)
{
	unsigned char i;
	
//	if(addr != 5 && addr != 6)
//	{
//		Time_Main_Over_Music = 1;
//	}
	sda=0;
	delay_ms(3); /*>2ms*/
	for(i=0;i<8;i++)
	{
		sda=1;
		if(addr&1)
		{
			delay_ms(3); /*>2400us*/
			sda=0;
			delay_ms(1); /*>800us*/
		}
		else
		{
			delay_ms(1); /*>800us*/
			sda=0;
			delay_ms(3); /*>2400us*/
		}
		addr>>=1;
	}
	sda=1;
	delay_ms(3);	
}

void Soundchime()
{
	GetRtcTime_Temp();
		
	NV080C_Play(Voice_content[RTC_YEAR_Temp/10]);
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_YEAR_Temp%10]);
		delay_ms(500);
	NV080C_Play(Voice_content[12]);
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_MONTH_Temp%10]);
		delay_ms(500);
	NV080C_Play(Voice_content[13]);
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_DAY_Temp/10]);
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_DAY_Temp%10]);
		delay_ms(500);
	NV080C_Play(Voice_content[14]);	
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_HOUR_Temp/10]);
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_HOUR_Temp%10]);
		delay_ms(500);
	NV080C_Play(Voice_content[11]);
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_MIN_Temp/10]);
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_MIN_Temp%10]);
		delay_ms(500);
	NV080C_Play(Voice_content[15]);	
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_SEC_Temp/10]);
		delay_ms(500);
	NV080C_Play(Voice_content[RTC_SEC_Temp%10]);
		delay_ms(500);
	NV080C_Play(Voice_content[16]);		
		delay_ms(500);
}

void GetRtcTime_Temp()
{
 	RTC_YEAR_Temp = RTC_YEAR;
	RTC_MONTH_Temp = RTC_MONTH;
	RTC_DAY_Temp = RTC_DAY;
	RTC_HOUR_Temp	= RTC_HOUR;				
	RTC_MIN_Temp = RTC_MIN;
	RTC_SEC_Temp = RTC_SEC;	
}