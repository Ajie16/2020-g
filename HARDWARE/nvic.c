/*******************************************************************************************
* NVIC-ALL中断管理代码
* 程序版本：V1.0
* 程序日期：2020-8-18
* 程序作者：徐杰
*******************************************************************************************/
#include "stm32f10x.h"

/*****************************************************************************
* 函  数：void NvicConfig(void)
* 功  能：配置工程中所有中断的优先级
* 参  数：无
* 返回值：无
* 备  注：此优先级中断不要随便更改哦
*****************************************************************************/
void NvicConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//时基中断
	NVIC_InitStruct.NVIC_IRQChannel=TIM4_IRQn;   //TIM4中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;   //抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;   //子优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;   //使能TIM4中断通道
	NVIC_Init(&NVIC_InitStruct);   //中断优先级初始化函数
	
		 //Usart1 NVIC 配置
  NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;		//子优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStruct);	//根据指定的参数初始化VIC寄存器
	
	  //Usart2 NVIC 配置
  NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;		//子优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStruct);	//根据指定的参数初始化VIC寄存器
}

