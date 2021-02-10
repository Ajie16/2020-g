#ifndef   _MAIN_H
#define   _MAIN_H

#include "stm32f10x_it.h" 
#include "stdio.h"
#include "stm32f10x.h"
#include "nvic.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "tim.h"
#include "motor.h"
#include "usart.h"
#include "usart2.h"
#include "pid.h"
#include "control.h"
#include "oled.h"
#include "key.h"
#include "beep.h"
#include "laser.h"
void System_Init(void);
void Task_Schedule(void);

#endif

