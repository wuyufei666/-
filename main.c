#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "mq2.h"
#include "adcx.h"
#include "key_nvic.h"
#include "timer.h"
#include "AD.h"



u16 value;
u8 buff[30];//参数显示缓存数组
float ppm;
extern u32 limit;
extern u32 flag;
int main(void)
{ 
	
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	//MQ2_Init();
	USART1_Config();//串口初始化
	
	Timer_Init();
  OLED_Init();
  beep_init();
	fun_init();
	KEY_NVIC_Config();
	AD_Init();
	
	OLED_Clear();
	//显示“烟雾浓度:”
	OLED_ShowChinese(0,0,0,16,1);
	OLED_ShowChinese(16,0,1,16,1);
	OLED_ShowChinese(32,0,2,16,1);
	OLED_ShowChinese(48,0,3,16,1);
	OLED_ShowChar(64,0,':',16,1);
	
	
	OLED_ShowString(0,45,"L:",16,1);
	OLED_ShowString(35,45,"ppm",16,1);
	



  while (1)
  {
		u32 ppm2=ppm;
		OLED_ShowNum(15,45,limit,2,16,1);
		OLED_ShowNum(85,45,flag,1,16,1);
		
		
		//value=AD_GetValue();
		//value = MQ2_GetData();  
		
		//value=value*5/4096*6.64*2;
		
		//printf("ppm:=%d \n\r",value);
		
		//ppm = AD_MQ2_GetData_PPM();
		//sprintf((char*)buff, "%.2fppm    ",ppm);
		//OLED_ShowString(48,16,buff,16,1);
		
		
		OLED_ShowString(48,16,"     ppm",16,1);
		OLED_ShowNum(80,0,value,4,16,1);
		
		
		if(value>limit)
		 {
			 beep_open();
			 fun_open();
		 }
		 else
		 {
			 beep_close();
			 fun_close();
		 }
		
		
		
	
		
		
		
//		 
//	   if(ppm2>limit)
//		 {
//			 beep_open();
//			 fun_open();
//		 }
//		 else
//		 {
//			 beep_close();
//			 fun_close();
//		 }
		delay_ms(20);

  }
	
}


void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)		//判断是否是TIM2的更新事件触发的中断
	{
    value = AD_GetValue(); 
    value=value*5/4096*6.64*2;
     printf("ppm:=%d \n\r",value);
				
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);			
		                          //清除TIM2更新事件的中断标志位											//中断标志位必须清除
														//否则中断将连续不断地触发，导致主程序卡死
	}
}



