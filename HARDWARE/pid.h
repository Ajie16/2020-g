#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"
typedef struct PID //PID�㷨�����ݽṹ 
{
  float P;         //����
  float I;
  float D;
  float Error;     //������
  float Integral;  //������
  float Differ;    //΢����
  float PreError;
  float PrePreError;
  float Ilimit; 
  float Irang;
  float Pout;
  float Iout;
  float Dout;
  float OutPut;   
  uint8_t Ilimit_flag;    //���ַ���	
}PID_TYPE;

//����������
void PidParameter_init(void);
void PID_Postion_Cal(PID_TYPE*PID,float target,float measure);

#endif
