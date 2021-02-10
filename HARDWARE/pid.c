/*******************************************************************************************
* PID套用代码
* 程序版本：V1.0
* 程序日期：2020-9-7
* 程序作者：徐
*******************************************************************************************/
#include "pid.h"
extern PID_TYPE PID_X,PID_Y;
/*****************************************************************************
* 函  数：void PID_Postion_Cal(PID_TYPE*PID,float target,float measure)
* 功  能：位置式PID算法
* 参  数：PID: 算法P I D参数的结构体
*         target: 目标值
*         measure: 测量值
* 返回值：无
* 备  注: PID输入输出套用函数
*****************************************************************************/
void PID_Postion_Cal(PID_TYPE*PID,float target,float measure)
{
	PID->Error  = target - measure;              //误差
	PID->Differ = PID->Error - PID->PreError;    //微分量
	PID->Pout = PID->P * PID->Error;                        //比例控制
	PID->Iout = PID->Ilimit_flag * PID->I * PID->Integral;  //积分控制
	PID->Dout = PID->D * PID->Differ;                       //微分控制
	PID->OutPut =  PID->Pout + PID->Iout + PID->Dout;       //比例 + 积分 + 微分总控制
	
	PID->Integral += PID->Error;                        //对误差进行积分
	if(PID->Integral > PID->Irang)                      //积分限幅
		PID->Integral = PID->Irang;
	if(PID->Integral < -PID->Irang)                     //积分限幅
		PID->Integral = -PID->Irang;                    
	PID->PreError = PID->Error ;                            //前一个误差值
}

/*****************************************************************************
* 函  数：void PidParameter_init(void)
* 功  能：初始化PID结构体里的成员值
* 参  数：无
* 返回值：无 
*****************************************************************************/
void PidParameter_init(void)
{
	PID_X.P=6.0;
	PID_X.I=0.0;
	PID_X.D=18.0;
	
	PID_X.Ilimit_flag=1;
	
	PID_Y.P=6.0;
	PID_Y.I=0;
	PID_Y.D=18.0;
	
	PID_Y.Ilimit_flag=1;
}


