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

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;   
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4; 
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;	
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}


