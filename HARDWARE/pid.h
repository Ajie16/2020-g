#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"
typedef struct PID //PID算法的数据结构 
{
  float P;         //参数
  float I;
  float D;
  float Error;     //比例项
  float Integral;  //积分项
  float Differ;    //微分项
  float PreError;
  float PrePreError;
  float Ilimit; 
  float Irang;
  float Pout;
  float Iout;
  float Dout;
  float OutPut;   
  uint8_t Ilimit_flag;    //积分分离	
}PID_TYPE;

//函数定义区
void PidParameter_init(void);
void PID_Postion_Cal(PID_TYPE*PID,float target,float measure);

#endif

