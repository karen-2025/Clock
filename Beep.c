#include "Beep.h"

sbit Beep = P5^2;       // ¶¨Òå·äÃùÆ÷¿ØÖÆ¶Ë


void Beep_Init()        // ·äÃùÆ÷³õÊ¼»¯£¬²»Ïì
{
  Beep = 1;
}


void Beep_shortSound()  // ·äÃùÆ÷µÎµÄÒ»ÉùÏì
{
  Beep = 0;
	delay_ms(20);
	Beep = 1;
}

void Beep_ClockSound()  // ·äÃùÆ÷ÄÖÖÓÏì
{
  Beep = 0;
	delay_ms(1000);
	Beep = 1;
	delay_ms(200);
	Beep = 0;
	delay_ms(1000);
	Beep = 1;
	delay_ms(200);
}
	