#include "Temperature.h"

sbit DQ=P1^5; 				//数据传输线接单片机的相应的引脚 
u8 tempL=0; 		      //设全局变量
u8 tempH=0; 
u8 sdata;			        //测量到的温度的整数部分
u8 xiaoshu1;		      //小数第一位
u8 xiaoshu2;		      //小数第二位
bit Tem_bit=1;        //温度正负标志

//延时函数
void delay(u16 i)
{
	for(i;i>0;i--);
}


void Init_DS18B20()   //DS18B20初始化设置
{
	u8 x=0;
	DQ=1; 					//DQ先置高 
	delay(20); 				//稍延时
	DQ=0; 					//发送复位脉冲 
	delay(480); 				//延时（>480us)   //（重要参数）
	DQ=1; 					//拉高数据线 
	delay(39); 				//等待（15~60us)  //  60us（卡在60us,重要参数）
	x=DQ; 					//用X的值来判断初始化有没有成功，18B20存在的话X=0，否则X=1 
	delay(200);     //（重要参数）
}

u8 ReadOneChar()  			//读一个字节，主机数据线先从高拉至低电平1us以上，再使数据线升为高电平，从而产生读信号
{
	u8 i=0; 		//每个读周期最短的持续时间为60us，各个读周期之间必须有1us以上的高电平恢复期
	u8 dat=0; 
	for (i=8;i>0;i--) 		//一个字节有8位 
	{
		EA=0;         // 非常重要的 指令，本程序里的中断会打断 DS18B20的 读写时序时间，此段需要先关掉中断，如果不关闭中断读温度将不可控
		DQ=0;
		delay(1);     // (重要参数)
		DQ=1;
		dat>>=1; 
		DQ=1; 
		delay(1);     // (重要参数)	
		if(DQ) 
		dat|=0x80; 
		delay(39);    // (重要参数)
		EA=1;         // 非常重要的 指令，读完后打开中断
	} 
	return(dat);
}

void WriteOneChar(u8 dat)   //写一个字节
{ 
	u8 i=0; 		     //数据线从高电平拉至低电平，产生写起始信号。15us之内将所需写的位送到数据线上，
	for(i=8;i>0;i--) 		//在15~60us之间对数据线进行采样，如果是高电平就写1，低写0发生。 
	{ 
 	  EA=0;         // 非常重要的 指令，本程序里的中断会打断 DS18B20的 读写时序时间，此段需要先关掉中断，如果不关闭中断读温度将不可控
		DQ=0; 				
    delay(1); 		
		DQ=dat&0x01; 
		delay(39); 
		DQ=1; 
		dat>>=1;
		EA=1;         // 非常重要的 指令，写完后打开中断
	} 
}


void ReadTemperature()        //读温度值（低位放tempL;高位放tempH;）
{ 
	Init_DS18B20(); 					  //初始化
	WriteOneChar(0xcc); 				//跳过读序列号的操作
	WriteOneChar(0x44); 				//启动温度转换
	delay(500); 						    //转换需要一点时间，延时 
	Init_DS18B20(); 					  //初始化
	WriteOneChar(0xcc); 				//跳过读序列号的操作  
	WriteOneChar(0xbe); 				//读温度寄存器（头两个值分别为温度的低位和高位） 
	tempL=ReadOneChar(); 				//读出温度的低位LSB
	tempH=ReadOneChar(); 				//读出温度的高位MSB	
	if(tempH>0x7f)      				//最高位为1时温度是负
	{
		tempL=~tempL;					//补码转换，取反加一
		tempH=~tempH+1;       
		Tem_bit=0;      						//读取温度为负时Tem_bit=0
	}
	sdata = tempL/16+tempH*16;      	//整数部分
	xiaoshu1 = (tempL&0x0f)*10/16; 		//小数第一位
	xiaoshu2 = (tempL&0x0f)*100/16%10;	//小数第二位
}


void Led(u16 date)  //显示函数
{ 
	if(Tem_bit==1)
	{	
	 ShowValue_A(date/10,date%10+20,xiaoshu1,xiaoshu2,41,31,31,31);  // 带小数点数值需要加20
	 ShowValue_B(31,31,31,31,31,31);		
	}		
}
	
void CurrentTemperature_Display()  // 显示当前温度
{
  if(Modenum4_bit == 1 && Modenum == 4)
	{
	  	ReadTemperature();
	    Led(sdata);
	}		
}
