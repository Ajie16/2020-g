#include "control.h"
#include "pid.h"
#include "motor.h"
#include "math.h"
#include "stdio.h"

extern s16 x,y;
//���
PID_TYPE PID_X;
PID_TYPE PID_Y;

void Control(void)//��ʱΪvoid
{	
	//���ƻ�
	PID_Postion_Cal(&PID_X,0.0,(float)x);
	PID_Postion_Cal(&PID_Y,0.0,(float)y);
	//PID���Ӻ�MOTO���
	Moto_Pwm((s16)PID_Y.OutPut,(s16)PID_X.OutPut);
}

