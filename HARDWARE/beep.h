#ifndef   __BEEP_H
#define   __BEEP_H

#include "sys.h"
/***************************************************************************
* �궨���� PB0-�� PB1-��
***************************************************************************/
#define BEEP_ON() PAout(5)=0
#define BEEP_OFF() PAout(5)=1
#define BEEP_FLASH() PAout(5)=~PAout(5)
void BEEP_Init(void);

#endif

