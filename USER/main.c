#include "head.h"
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//WK_UP的输入端口
int main(void)
{
	u16 count=0;
	u8 control=1;
	KEY_Confrigration();
	TIM1_PWM_Confriguration();//声明TIM1初始化函数
	
	while(1)
	{
		if(WK_UP)delay_ms(1);
		else delay_ms(5);
		if(control)count++;
		else count--;
		if(count>450)control=0;
		if(count==0) control=1;
		TIM_SetCompare1(TIM1,count);//实时改变PWM的占空比
	}
}

