#include "led.h"
#include "delay.h"

void LED_Init(void)
{
	//开启GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//配置LED引脚为模拟输出模式
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PROT, &GPIO_InitStructure);
	GPIO_ResetBits(LED_GPIO_PROT, LED_GPIO_PIN);
}

void beep_init()
{
	//beep A5   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
															//使用各个外设前必须开启时钟，否则对外设的操作无效
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				//GPIO引脚，赋值为第0号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);		//将赋值后的构体变量传递给GPIO_Init函数
	
	GPIO_SetBits(GPIOA, GPIO_Pin_5);	
}


void beep_open(void)
{
  GPIO_ResetBits(GPIOA, GPIO_Pin_5);		
}
void beep_close(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_5);	
}
void fun_init()
{
	//fun a6   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
															//使用各个外设前必须开启时钟，否则对外设的操作无效
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				//GPIO引脚，赋值为第0号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
}


void fun_open(void)
{
  GPIO_SetBits(GPIOA, GPIO_Pin_6);		
}
void fun_close(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);	
}


//void fun_pwm_init()
//{
//	//开启TIM3和GPIOA的时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	//初始化GPIO口 PA6 PA7 用于产生PWM信号
//	GPIO_InitTypeDef GPIO_InitStructure;
//	//复用推挽输出模式因为复用了TIM3外设
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO A6 A7 
//	//使用内部时钟
//	TIM_InternalClockConfig(TIM3);
//	//配置时基单元参数
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//定时器不分频
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
//	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;//ARR自动重装值
//	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;//PSC预分频值
//	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//到达ARR触发一次中断 停止计数
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);//初始化单元
//	//输出比较结构体配置
//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure);//补全结构体中未配置参数
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;	
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择PWM模式1
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出比较极性选择
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出使能

//	TIM_OC1Init(TIM3, &TIM_OCInitStructure);//初始化 TIM3 OC1
//	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能CCR1自动重装
//	
//	TIM_ARRPreloadConfig(TIM3,ENABLE);//开启预装载
//	TIM_Cmd(TIM3, ENABLE);//开启定时器3
//	TIM3->CCR1 = 0;//设置输出比较值
//}

////设置PWM1比较值 为Compare 即输出比较值
//void fun_speed(uint16_t Compare)   //0---1000
//{
//	TIM_SetCompare1(TIM3, Compare);
//}

void LED_Toggle(void)
{
	GPIO_WriteBit(LED_GPIO_PROT, LED_GPIO_PIN, (BitAction)((1-GPIO_ReadOutputDataBit(LED_GPIO_PROT, LED_GPIO_PIN))));//led电平翻转
}
void LED_On()
{
	GPIO_ResetBits(LED_GPIO_PROT, LED_GPIO_PIN);
}
void LED_Off()
{
	GPIO_SetBits(LED_GPIO_PROT, LED_GPIO_PIN);
}

void LED_Twinkle()
{
	LED_On();
	delay_ms(10);
	LED_Off();
}
