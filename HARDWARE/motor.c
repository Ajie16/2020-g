/*******************************************************************************************
* PWM输出配置
* 程序版本：V1.0
* 程序日期：2020-8-18
* 程序作者：徐杰
*******************************************************************************************/
#include "stm32f10x.h"
#include "delay.h"
/*******************************************************************************************
* 姿态平衡电机宏定义
*******************************************************************************************/
#define Moto_PwmMax 2
#define Moto_PwmMin -2
int16_t MOTO1_PWM = 0;
int16_t MOTO2_PWM = 0;
/******************************************************************************************
* 函  数：void MOTOR_Init(void)
* 功  能：电机引脚初始化 以及TIM3 配置输出PWM
* 参  数：无
* 返回值：无
* 备  注：TIM1 CH1(PWM1) -> PA8
*         TIM1 CH4(PWM4) -> PA11
*******************************************************************************************/
void MOTOR_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;   //定义GPIO结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;   //定义定时器结构体变量
	TIM_OCInitTypeDef TIM_OCInitStruct;   //定义输出比较结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE); 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);   //使能TIM2的时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;   //配置GPIO第6、7引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;   	  //配置GPIO为复用推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;  	  //配置GPIO速率
	GPIO_Init(GPIOA,&GPIO_InitStruct);   //GPIO初始化函数
	
	
	TIM_TimeBaseInitStruct.TIM_Period=19999;   	  //设置自动重装载的周期值
	TIM_TimeBaseInitStruct.TIM_Prescaler=71;   	  //设置预分频值
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;     //设置时钟分割
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);   		   //定时器初始化函数
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;   //PWM模式1
	TIM_OCInitStruct.TIM_Pulse=0;   						   //初始化占空比为0
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;   	   //输出比较极性低
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;   //比较输出使能
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);   					   //比较输出初始化函数
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);   //输出比较1预装载寄存器使能
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;   //PWM模式1
	TIM_OCInitStruct.TIM_Pulse=0;   							//初始化占空比为0
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;   		//输出比较极性低
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;   	//比较输出使能
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);   						//比较输出初始化函数
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);   //输出比较4预装载寄存器使能
	
	TIM_Cmd(TIM2,ENABLE);  
	
}

/************************************************************************************************
* 函  数：void Moto_Pwm(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
* 功  能：电机要输出数值转换成PWM波形输出
* 参  数：MOTO1_PWM 电机1
*         MOTO2_PWM 电机2
*         MOTO3_PWM 电机3
*         MOTO3_PWM 电机4
* 返回值：无 
* 备  注：无
************************************************************************************************/
void Moto_Pwm(int16_t MOTO1_PWM,int16_t MOTO2_PWM)
{	
	s16 pwm1,pwm2;
	if(MOTO1_PWM>Moto_PwmMax)	MOTO1_PWM = Moto_PwmMax;
	if(MOTO2_PWM>Moto_PwmMax)	MOTO2_PWM = Moto_PwmMax;

	if(MOTO1_PWM<Moto_PwmMin)	MOTO1_PWM = Moto_PwmMin;
	if(MOTO2_PWM<Moto_PwmMin)	MOTO2_PWM = Moto_PwmMin;
	
	pwm1 = TIM_GetCapture1(TIM2)-MOTO1_PWM;
	pwm2 = TIM_GetCapture2(TIM2)+MOTO2_PWM;
	if(pwm1>=2500)
		pwm1=2500;
	if(pwm1<=2200)
		pwm1=2200;
	
	if(pwm2>=2200)
		pwm2=2200;
	if(pwm2<=1800)
		pwm2=1800;
	
	TIM2->CCR1=pwm1;
	TIM2->CCR2=pwm2;
}

