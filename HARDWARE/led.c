/*******************************************************************************************
* LED��ʾ
* ����汾��V1.0
* �������ڣ�2020-8-18
* �������ߣ����
*******************************************************************************************/
#include "stm32f10x.h"



/***************************************************************************
* ��  ����void LED_Init(void)
* ��  �ܣ��û�ָʾ�����ų�ʼ��
* ��  ������
* ����ֵ����
* ��  ע: ��
***************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;   
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13; 
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;	
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOC,&GPIO_InitStruct);

}

