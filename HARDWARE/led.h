#ifndef   _LED_H
#define   _LED_H

#include "sys.h"
/***************************************************************************
* �궨���� PB0-�� PB1-��
***************************************************************************/
#define LED_ON() PCout(13)=0
#define LED_OFF() PCout(13)=1
#define LED_FLASH() PCout(13)=~PCout(13)
void LED_Init(void);

#endif

