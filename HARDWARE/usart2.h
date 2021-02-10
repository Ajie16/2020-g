#ifndef   __USART2_H
#define   __USART2_H
#include "stdint.h"
#include "stm32f10x.h"
void usart2_init(uint32_t bound);
void usart2_send(uint8_t *data,uint8_t len);
void Usart_Write_Bytes(USART_TypeDef* USARTx, unsigned char *pdata, int length);

#endif

