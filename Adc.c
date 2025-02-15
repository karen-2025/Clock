#include "Adc.h"

sbit BatteryLowLed = P5^3;      // 电量不足指示灯
u16 Result_ADC15;               //15通道的ADC结果
u16 VCC_Power;                  //电池电压

void BatteryAdc_Init()
{  	
	  BatteryLowLed = 0;          // 初始化指示灯灭
	  P_SW2 |= 0x80;
    ADCTIM = 0x3f;              //设置ADC内部时序
    ADCCFG = 0x0f;              //设置ADC时钟为系统时钟/2/16, 12位转换结果
    ADC_CONTR = 0x8f;           //使能ADC模块,选定 15通道 
    EADC = 1;                   //使能ADC中断
    EA = 1;
    ADC_CONTR |= 0x40;          //启动AD转换
}

void ADC_Isr() interrupt 5
{
    ADC_CONTR &= ~0x20;                                     //清中断标志
    Result_ADC15 = ADC_RES;                                 //读取15通道的ADC结果,取高8位就够了
	  VCC_Power = (u16)(255*1.19*1000/ Result_ADC15);         //(8位ADC算法)计算VREF管脚电压,即电池电压，注意这里是 mv
	
		if(VCC_Power < 3750)                                    // 电池电压设定 3.75V 为需要提醒充电的电压门槛
			P53 = 1;                                              // 注意在接近门槛电压时，有时按键切换，显示灯会亮灭，因为 电压会随功能不同而变化，属于正常
		else if(VCC_Power >= 3750)
			P53 = 0;  	
		if(Modenum5_bit == 1 && Modenum == 5)                  // 显示当前电池几V
		  QuantityOfBattery_Display();
		
    ADC_CONTR |= 0x40;            //继续AD转换
}

void QuantityOfBattery_Display()
{
	Display_Day(0 ,  VCC_Power/1000+20);       // 显示 第一行 第 0 个数码管，带小数点
	Display_Day(1 ,  VCC_Power/100%10);    
	Display_Day(2 ,  VCC_Power%100/10);      
	Display_Day(3 , 43);	                     // 显示 V,用 U 表示
	Display_Day(4 , 31);   
	Display_Day(5 , 31);           
	Display_Day(6 , 31);    
	Display_Day(7 , 31);	   
	
	Display_Time(0 , 31);	    // 第二行数码管不显示内容
	Display_Time(1 , 31);   
	Display_Time(2 , 31);
	Display_Time(3 , 31);
	Display_Time(4 , 31);	
	Display_Time(5 , 31);		
}
