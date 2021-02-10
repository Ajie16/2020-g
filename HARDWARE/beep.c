/*******************************************************************************************
* LED显示
* 程序版本：V1.0
* 程序日期：2020-8-18
* 程序作者：徐杰
*******************************************************************************************/
#include "stm32f10x.h"

/***************************************************************************
* 函  数：void LED_Init(void)
* 功  能：用户指示灯引脚初始化
* 参  数：无
* 返回值：无
* 备  注: 无
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


