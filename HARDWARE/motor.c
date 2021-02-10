/*******************************************************************************************
* PWM�������
* ����汾��V1.0
* �������ڣ�2020-8-18
* �������ߣ����
*******************************************************************************************/
#include "stm32f10x.h"
#include "delay.h"
/*******************************************************************************************
* ��̬ƽ�����궨��
*******************************************************************************************/
#define Moto_PwmMax 2
#define Moto_PwmMin -2
int16_t MOTO1_PWM = 0;
int16_t MOTO2_PWM = 0;
/******************************************************************************************
* ��  ����void MOTOR_Init(void)
* ��  �ܣ�������ų�ʼ�� �Լ�TIM3 �������PWM
* ��  ������
* ����ֵ����
* ��  ע��TIM1 CH1(PWM1) -> PA8
*         TIM1 CH4(PWM4) -> PA11
*******************************************************************************************/
void MOTOR_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;   //����GPIO�ṹ�����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;   //���嶨ʱ���ṹ�����
	TIM_OCInitTypeDef TIM_OCInitStruct;   //��������ȽϽṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE); 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);   //ʹ��TIM2��ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;   //����GPIO��6��7����
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;   	  //����GPIOΪ�����������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;  	  //����GPIO����
	GPIO_Init(GPIOA,&GPIO_InitStruct);   //GPIO��ʼ������
	
	
	TIM_TimeBaseInitStruct.TIM_Period=19999;   	  //�����Զ���װ�ص�����ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler=71;   	  //����Ԥ��Ƶֵ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;     //����ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);   		   //��ʱ����ʼ������
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;   //PWMģʽ1
	TIM_OCInitStruct.TIM_Pulse=0;   						   //��ʼ��ռ�ձ�Ϊ0
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;   	   //����Ƚϼ��Ե�
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;   //�Ƚ����ʹ��
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);   					   //�Ƚ������ʼ������
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);   //����Ƚ�1Ԥװ�ؼĴ���ʹ��
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;   //PWMģʽ1
	TIM_OCInitStruct.TIM_Pulse=0;   							//��ʼ��ռ�ձ�Ϊ0
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;   		//����Ƚϼ��Ե�
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;   	//�Ƚ����ʹ��
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);   						//�Ƚ������ʼ������
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);   //����Ƚ�4Ԥװ�ؼĴ���ʹ��
	
	TIM_Cmd(TIM2,ENABLE);  
	
}

/************************************************************************************************
* ��  ����void Moto_Pwm(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
* ��  �ܣ����Ҫ�����ֵת����PWM�������
* ��  ����MOTO1_PWM ���1
*         MOTO2_PWM ���2
*         MOTO3_PWM ���3
*         MOTO3_PWM ���4
* ����ֵ���� 
* ��  ע����
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
