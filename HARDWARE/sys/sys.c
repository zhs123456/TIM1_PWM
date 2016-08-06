#include "sys.h"




/***************************************************************************
*使用KEY时打开此函数
*KEY的IO口配置函数
***************************************************************************/
void KEY_Confrigration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//结构体变量的声明
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//WK_UP-->PA.0 端口配置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//IO 口速度为 50MHz(作为输入时不用设置速率)
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//GPIOA0下拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);//根据设定参数初始化 GPIOA.0
}






/***************************************************************************
*使用TIM1用来产生PWM时打开此函数
*TIM1的初始化函数
***************************************************************************/
#define arr 899
#define psc 0
void TIM1_PWM_Confriguration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//结构体变量的声明
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//初始化定时器参数的结构体变量初始化
	TIM_OCInitTypeDef TIM_OCInitStructure;//PWM 模式及通道方向设置的结构体变量初始化
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//使能TIM1定时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能GPIO端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM1_CH1-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO 口速度为 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure); //根据设定参数初始化 GPIOB.8
	
	TIM_TimeBaseStructure.TIM_Period = arr;//设置自动重装载寄存器周期的值，保证每次更新中断间隔为10ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc;//设置时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 1;//分频1模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);//根据设置的参数初始化定时器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //脉宽调制模式 2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse=0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); //根据TIM_OCInitStruct中指定的参数初始化外设 TIMx
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); //MOE主输出使能（必须设置）
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH1 预装载使能
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能 TIMx 在 ARR 上的预装载寄存器
	 
	TIM_Cmd(TIM1, ENABLE); //使能 TIM1外设（即开启TIM1定时器）
	
}




