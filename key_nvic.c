#include "key_nvic.h"
u32 limit=30;
u32 flag=0;
 
void KEY_NVIC_Config(void)			//配置 主控按键触发
{
	EXTI_InitTypeDef KEY_NVIC;
	NVIC_InitTypeDef key_NVIC;
	
	//开启IO口复用时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//GPIO初始化——部分
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//开启GPIOA的时钟
															//使用各个外设前必须开启时钟，否则对外设的操作无效
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//GPIO模式，
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//GPIO引脚，赋值为第10号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);	//将PB0映射到外部中断线0
	
	//外部中断初始化——部分
	KEY_NVIC.EXTI_Line = EXTI_Line0;												// 中断线：0 
	KEY_NVIC.EXTI_LineCmd = ENABLE;													// 使能
	KEY_NVIC.EXTI_Mode = EXTI_Mode_Interrupt;								// 产生 中断
	KEY_NVIC.EXTI_Trigger = EXTI_Trigger_Falling;						// 下降沿 触发
	EXTI_Init(&KEY_NVIC);
	
	//中断优先级 初始化
	key_NVIC.NVIC_IRQChannel = EXTI0_IRQn;
	key_NVIC.NVIC_IRQChannelCmd = ENABLE;
	key_NVIC.NVIC_IRQChannelPreemptionPriority = 2;
	key_NVIC.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&key_NVIC);
	
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//GPIO模式，
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				//GPIO引脚，赋值为第1号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);	//将PB0映射到外部中断线0
	
	KEY_NVIC.EXTI_Line = EXTI_Line1;												// 中断线：0 
	KEY_NVIC.EXTI_LineCmd = ENABLE;													// 使能
	KEY_NVIC.EXTI_Mode = EXTI_Mode_Interrupt;								// 产生 中断
	KEY_NVIC.EXTI_Trigger = EXTI_Trigger_Falling;						// 下降沿 触发
	EXTI_Init(&KEY_NVIC);
	
	//中断优先级 初始化
	key_NVIC.NVIC_IRQChannel = EXTI1_IRQn;
	key_NVIC.NVIC_IRQChannelCmd = ENABLE;
	key_NVIC.NVIC_IRQChannelPreemptionPriority = 2;
	key_NVIC.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&key_NVIC);
}
 
void EXTI0_IRQHandler(void)
{
	
	delay_ms(100);
	if(flag==1)
	{
	limit=limit+5;
	if(limit>60)
	{
		limit=20;
	}
  }
	
	EXTI_ClearITPendingBit(EXTI_Line0);		//清除中断 标志位
}

void EXTI1_IRQHandler(void)
{
	
	//delay_ms(100);
	if(flag==0)
	{
		flag=1;
	}
	else
	{
		flag=0;
	}

	EXTI_ClearITPendingBit(EXTI_Line1);		//清除中断 标志位
}
