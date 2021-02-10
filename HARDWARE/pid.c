/*******************************************************************************************
* PID���ô���
* ����汾��V1.0
* �������ڣ�2020-9-7
* �������ߣ���
*******************************************************************************************/
#include "pid.h"
extern PID_TYPE PID_X,PID_Y;
/*****************************************************************************
* ��  ����void PID_Postion_Cal(PID_TYPE*PID,float target,float measure)
* ��  �ܣ�λ��ʽPID�㷨
* ��  ����PID: �㷨P I D�����Ľṹ��
*         target: Ŀ��ֵ
*         measure: ����ֵ
* ����ֵ����
* ��  ע: PID����������ú���
*****************************************************************************/
void PID_Postion_Cal(PID_TYPE*PID,float target,float measure)
{
	PID->Error  = target - measure;              //���
	PID->Differ = PID->Error - PID->PreError;    //΢����
	PID->Pout = PID->P * PID->Error;                        //��������
	PID->Iout = PID->Ilimit_flag * PID->I * PID->Integral;  //���ֿ���
	PID->Dout = PID->D * PID->Differ;                       //΢�ֿ���
	PID->OutPut =  PID->Pout + PID->Iout + PID->Dout;       //���� + ���� + ΢���ܿ���
	
	PID->Integral += PID->Error;                        //�������л���
	if(PID->Integral > PID->Irang)                      //�����޷�
		PID->Integral = PID->Irang;
	if(PID->Integral < -PID->Irang)                     //�����޷�
		PID->Integral = -PID->Irang;                    
	PID->PreError = PID->Error ;                            //ǰһ�����ֵ
}

/*****************************************************************************
* ��  ����void PidParameter_init(void)
* ��  �ܣ���ʼ��PID�ṹ����ĳ�Աֵ
* ��  ������
* ����ֵ���� 
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


