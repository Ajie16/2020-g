/*******************************************************************************************
* 中断服务函数编写
* 程序版本：V1.0
* 程序日期：2020-8-18
* 程序作者：徐杰
*******************************************************************************************/

#include "main.h"

/******************************************************************************/
/*                                全局变量                                     */
/******************************************************************************/
uint8_t KEY_Scan = 0;
uint8_t CTR_Scan = 0;
uint8_t SER_Scan = 0;
uint8_t IRQ_Scan = 0;
uint8_t BEEP_SCAN=0;

extern u8  USART2_RX_BUF[200];
extern u16  USART2_RX_STA;

/******************************************************************************/
/*                                内部函数                                     */
/******************************************************************************/
void NMI_Handler(void)
{
}
	//错误报警
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1){}
}
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1){}
}
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
    while (1){}
}
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
    while (1){}
}
void SVC_Handler(void)
{
}
void DebugMon_Handler(void)
{
}
void PendSV_Handler(void)
{
}
void SysTick_Handler(void)
{
}
/******************************************************************************/
/*                                外设函数                                     */
/******************************************************************************/

void TIM4_IRQHandler(void)   //TIM4中断服务函数
{
	static uint16_t ms5 = 0,ms10 = 0,ms20 = 0,ms100 = 0,ms200 = 0; //分频系数
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)	//判断是否进入TIM更新中断
	{
		
		ms5++;
		ms20++;
		ms10++;		
		ms100++;
		ms200++;
		if(ms5 >= 5)//200Hz
		{
			ms5 = 0;
			BEEP_SCAN=1;
		}
		if(ms10 >= 10)//100Hz
		{
			ms10 = 0;
			SER_Scan = 1;
		}
		if(ms20 >= 20)//50Hz
		{
			ms20 = 0;
			KEY_Scan = 1;
		}
		if(ms100 >= 100)//
		{
			ms100 = 0;
			CTR_Scan = 1;
		}
		if(ms200 >= 200)//5Hz
		{
			ms200 = 0;
			IRQ_Scan = 1;
		}
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	//清除TIM4更新中断
}

void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	u8 Res;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		
		if((USART2_RX_STA&0x8000)==0)//接收未完成
			{	
				if((USART2_RX_STA&0x1FFF)==9)
				{
					 USART2_RX_STA |= 0x8000;
				}
				
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
				}
			}
			 		 
   } 		
} 



void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		
		if((USART1_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART1_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
						USART1_RX_STA=0;//接收错误,重新开始
					else 
						USART1_RX_STA|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)
					USART1_RX_STA|=0x4000;
				else
					{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
    } 
} 

