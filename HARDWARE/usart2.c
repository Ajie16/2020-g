/*******************************************************************************************
* 串口初始化
* 程序版本：V1.0
* 程序日期：2020-8-18
* 程序作者：徐杰
*******************************************************************************************/
#include "stm32f10x.h"
#include "usart.h"

u8 USART2_RX_BUF[USART_REC_LEN];
u16 USART2_RX_STA;

/*****************************************************************************
* 函  数：void usart2_init(uint32_t baudrate)
* 功  能: 串口2的初始化
* 参  数: bud 波特率
* 返回值：无
* 备  注: 无
*****************************************************************************/
void usart2_init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART1，GPIOA时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	//USART1_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口1 
}
/*****************************************************************************
* 函  数：void usart_send(uint8_t *data,uint8_t len)
* 功  能: 串口发送函数
* 参  数: data-发送数据，len-字长
* 返回值：无
* 备  注: 无
*****************************************************************************/
void Usart_Write_Bytes(USART_TypeDef* USARTx, unsigned char *pdata, int length)
{
    int i = 0;
    for(i = 0; i < length; i++)
    {
        USART_SendData(USARTx, pdata[i]);
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        {}
    }
}






