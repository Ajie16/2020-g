#ifndef   __BEEP_H
#define   __BEEP_H

#include "sys.h"
/***************************************************************************
* ºê¶¨ÒåÇø PB0-ÂÌ PB1-ºì
***************************************************************************/
#define BEEP_ON() PAout(5)=0
#define BEEP_OFF() PAout(5)=1
#define BEEP_FLASH() PAout(5)=~PAout(5)
void BEEP_Init(void);

#endif

