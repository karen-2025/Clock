#ifndef __UART_H
#define __UART_H

#include "STC8H4K64TL.h"

extern bit  Rec_OK ;
extern u8 xdata rtctime[12];
void	UART1_config(u32 clk, u32 brt);

#endif

