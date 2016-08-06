#include "sys.h"




/***************************************************************************
*ʹ��KEYʱ�򿪴˺���
*KEY��IO�����ú���
***************************************************************************/
void KEY_Confrigration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//�ṹ�����������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA��ʱ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//WK_UP-->PA.0 �˿�����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//IO ���ٶ�Ϊ 50MHz(��Ϊ����ʱ������������)
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//GPIOA0��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);//�����趨������ʼ�� GPIOA.0
}






/***************************************************************************
*ʹ��TIM1��������PWMʱ�򿪴˺���
*TIM1�ĳ�ʼ������
***************************************************************************/
#define arr 899
#define psc 0
void TIM1_PWM_Confriguration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//�ṹ�����������
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//��ʼ����ʱ�������Ľṹ�������ʼ��
	TIM_OCInitTypeDef TIM_OCInitStructure;//PWM ģʽ��ͨ���������õĽṹ�������ʼ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//ʹ��TIM1��ʱ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIO�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM1_CH1-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO ���ٶ�Ϊ 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure); //�����趨������ʼ�� GPIOB.8
	
	TIM_TimeBaseStructure.TIM_Period = arr;//�����Զ���װ�ؼĴ������ڵ�ֵ����֤ÿ�θ����жϼ��Ϊ10ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc;//����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 1;//��Ƶ1ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);//�������õĲ�����ʼ����ʱ��
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //�������ģʽ 2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse=0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������ TIMx
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); //MOE�����ʹ�ܣ��������ã�
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH1 Ԥװ��ʹ��
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���
	 
	TIM_Cmd(TIM1, ENABLE); //ʹ�� TIM1���裨������TIM1��ʱ����
	
}




