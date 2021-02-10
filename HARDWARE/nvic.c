/*******************************************************************************************
* NVIC-ALL�жϹ������
* ����汾��V1.0
* �������ڣ�2020-8-18
* �������ߣ����
*******************************************************************************************/
#include "stm32f10x.h"

/*****************************************************************************
* ��  ����void NvicConfig(void)
* ��  �ܣ����ù����������жϵ����ȼ�
* ��  ������
* ����ֵ����
* ��  ע�������ȼ��жϲ�Ҫ������Ŷ
*****************************************************************************/
void NvicConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//ʱ���ж�
	NVIC_InitStruct.NVIC_IRQChannel=TIM4_IRQn;   //TIM4�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;   //��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;   //�����ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;   //ʹ��TIM4�ж�ͨ��
	NVIC_Init(&NVIC_InitStruct);   //�ж����ȼ���ʼ������
	
		 //Usart1 NVIC ����
  NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStruct);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	  //Usart2 NVIC ����
  NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStruct);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

