#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//��ȡ����0
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//��ȡ����1
 

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	  2	//KEY1����
#define KEY2_PRES 	3	//KEY0����
#define KEY3_PRES	  4	//KEY1����

void KEY_Init(void);//IO��ʼ��
u8 KEY_SCAN(u8);  	//����ɨ�躯��					    
#endif