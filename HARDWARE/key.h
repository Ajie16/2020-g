#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//读取按键0
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//读取按键1
 

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	  2	//KEY1按下
#define KEY2_PRES 	3	//KEY0按下
#define KEY3_PRES	  4	//KEY1按下

void KEY_Init(void);//IO初始化
u8 KEY_SCAN(u8);  	//按键扫描函数					    
#endif
