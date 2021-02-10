/*******************************************************************************************
* BSP��ʼ���Լ��������
* ����汾��V1.0
* �������ڣ�2020-8-18
* �������ߣ����
*******************************************************************************************/
#include "main.h"

//�ⲿ����
extern u8  USART2_RX_BUF[USART_REC_LEN];
extern u8  USART2_RX_BUF[USART_REC_LEN];
extern u16 USART2_RX_STA;
extern u16 USART1_RX_STA;

extern uint8_t KEY_Scan ;
extern uint8_t CTR_Scan ;
extern uint8_t SER_Scan ;
extern uint8_t IRQ_Scan ;
extern uint8_t BEEP_SCAN;
extern void Control(void);

u8 key,lsb,msb,SCAN_Mode,mark,read_ok=0,last_read=0,mark_show=0;
u16 X=2400,Y=2000,result = 0,check = 0,mark2;
s32 x,y,l,len =0;
float dat,m; 
s8 ERR_X=1;
void System_Init(void)	//��ʼ��
{
	//�жϹ���
	NvicConfig();
	//��ʱ������ʼ��
	delay_init();
	//ʱ����ʼ��
	TIM_Init();
	//OLED��ʼ��
	OLED_Init();
	//������ʼ��
	KEY_Init();
	//LED��ʼ��
	LED_Init();
	//BEEP
	BEEP_Init();
	//���ڳ�ʼ��
	uart_init(115200);
	usart2_init(38400);
	//���������ʼ�� 
	PidParameter_init();
	MOTOR_Init();
	TIM_SetCompare1(TIM2,X);
	TIM_SetCompare2(TIM2,Y);
}

void Task_Schedule(void)
{
		if(KEY_Scan) //20ms
		{
			KEY_Scan = 0;
			//���ݴ�ӡ
			OLED_ShowString(0,0,"TEST",16);
			key=KEY_SCAN(0);
			
			if(key!=0)
			{
				if(key==KEY0_PRES)
				{
					//��λ
					SCAN_Mode = 0;
					PAout(4)=1;
					mark=0;
					x=0;y=0;
					TIM2->CCR1=X;
					TIM2->CCR2=Y;
					
					OLED_ShowString(56,48,"0",16);
				}
				if(key==KEY1_PRES)
				{
					TIM2->CCR1=X;
					TIM2->CCR2=Y;
					
					SCAN_Mode = 3;
					mark=0;
					mark_show=0;
					OLED_ShowString(56,48,"0",16);
				}
				if(key==KEY2_PRES)
				{
					TIM2->CCR1=X;
					TIM2->CCR2=Y;
					
					SCAN_Mode = 2;
					mark_show=0;
					if(mark==1)
					{
						 
						OLED_ShowString(56,48,"0",16);
						mark=0;
					}
					else
					{
						OLED_ShowString(56,48,"1",16);
						mark=1;
					}
				}
				if(key==KEY3_PRES)
				{
					
				}
				
				OLED_ShowNum(0,0,key,3,16);
			}
			OLED_Refresh_Gram();
		}
		
		
		

		
		if(SCAN_Mode==1) 	//���ݲ���
		{		
			SCAN_Mode=0;
			//��ȡ����
			OLED_ShowString(35,0,"Dis:",16);
			
			m=(float)(0.0315*result/100-0.0261)*l;
			m=m*100;
			if(USART1_RX_BUF[8]=='S')
			{
				OLED_ShowString(16,16,"Squ L:",16);
				OLED_ShowNum(72,16,m,4,16);
			}
			else if(USART1_RX_BUF[8]=='C')
			{
				OLED_ShowString(16,16,"Cyc R:",16);
				OLED_ShowNum(72,16,m,4,16);
			}
			else if(USART1_RX_BUF[8]=='T')
			{
				OLED_ShowString(16,16,"Tri L:",16);
				OLED_ShowNum(72,16,m,4,16);
			}
			SCAN_Mode=10;//���ж�
		}
		
		if(SER_Scan==1 && (SCAN_Mode==2) ) //��λ
		{
			SER_Scan=0;
			TIM2->CCR2 +=ERR_X;
			if(TIM2->CCR2>=2200)
			{
				TIM2->CCR2=2200;
				ERR_X=-1*ERR_X;	
			}
			if(TIM2->CCR2<=1800)
			{
				TIM2->CCR2=1800;
				ERR_X=-1*ERR_X;		
			}
			if(USART1_RX_BUF[9]=='Y')
				SCAN_Mode=3;

			
		}
		//��λ����
		if(CTR_Scan) 
		{
			CTR_Scan=0;
			if(SCAN_Mode==3)
				Control();
			//100msѭ����1��0
			if(mark==0)
			{
				printf("0\r\n");
			}
			else if(mark==1)
			{
				printf("1\r\n");
			}
		}
		
		if(IRQ_Scan) //200ms
		{
			IRQ_Scan=0;
			Get_Meas_Dis(1);
			LED_FLASH();
			//���������ʾ
			if((x>=-2 && x<=2) && (y>=-2 && y<=2) && ((SCAN_Mode==1) || (SCAN_Mode == 3)) && USART1_RX_BUF[9]=='Y')
			{
				read_ok++;
			}
			if(read_ok!=0 && ((SCAN_Mode==1) || (SCAN_Mode == 3)) && USART1_RX_BUF[9]=='Y')
			{
				last_read++;
			}
			
			if((read_ok == 10) && (mark_show==0) && ((SCAN_Mode==1) || (SCAN_Mode == 3)) && USART1_RX_BUF[9]=='Y')
			{
				if(read_ok == last_read)
				{
					read_ok=0;
					last_read=0;
					mark_show=1;
					SCAN_Mode=1;//��ʾ����
				}
				else
				{
					read_ok=0;
					last_read=0;
				}
			}
		}
		
				
		if(BEEP_SCAN)//5ms
		{
			BEEP_SCAN=0;
			if(mark_show==1 && (SCAN_Mode==1 || SCAN_Mode==3 || SCAN_Mode==10) && USART1_RX_BUF[9]=='Y')
			{
				PAout(4)=0;
    		mark2++;
				if(mark2==400)
				{
					mark2=0;
					PAout(4)=1;
					mark_show=0;
				}
			}
		}
		
		//OPENMV��λ������(����1)
		if(USART1_RX_STA&0x8000)
		{
			USART1_RX_STA=0;
			l=(USART1_RX_BUF[10]-'0')*100+(USART1_RX_BUF[11]-'0')*10+(USART1_RX_BUF[12]-'0');
			
			if((USART1_RX_BUF[0]=='x') && (USART1_RX_BUF[4]=='y'))
			{
				if(USART1_RX_BUF[1] != '-')
				{
					x=(USART1_RX_BUF[1]-'0')*100+(USART1_RX_BUF[2]-'0')*10+(USART1_RX_BUF[3]-'0');
				
				}else
					x=-(USART1_RX_BUF[2]-'0')*10-(USART1_RX_BUF[3]-'0');
				
				if(USART1_RX_BUF[5] != '-')
				{
					y=(USART1_RX_BUF[5]-'0')*100+(USART1_RX_BUF[6]-'0')*10+(USART1_RX_BUF[7]-'0');
				}else
					y=-(USART1_RX_BUF[6]-'0')*10-(USART1_RX_BUF[7]-'0');
			
			}
			if(x>=0)
			{
				OLED_ShowChar(0,32,'+',16,1);
				OLED_ShowNum(8,32,x,3,16);
			}
			else
			{
				OLED_ShowChar(0,32,'-',16,1);
				OLED_ShowNum(8,32,-x,3,16);
			}
			
			if(y>=0)
			{
				OLED_ShowChar(0,48,'+',16,1);
				OLED_ShowNum(8,48,y,3,16);
			}
			else
			{
				OLED_ShowChar(0,48,'-',16,1);
				OLED_ShowNum(8,48,-y,3,16);
			}
			
			if(USART1_RX_BUF[13]=='N')
				OLED_ShowString(40,32,"Normal",16);
			if(USART1_RX_BUF[13]=='B')
				OLED_ShowString(40,32,"Basket",16);
			if(USART1_RX_BUF[13]=='S')
				OLED_ShowString(40,32,"Soccer",16);
			if(USART1_RX_BUF[13]=='V')
				OLED_ShowString(40,32,"Volley",16);
		}
		//�����ദ����(����2)
			if(USART2_RX_STA&0x8000)
		{
			USART2_RX_STA=0;
			len = sizeof(USART2_RX_BUF);
			check = CRC16(USART2_RX_BUF, len-2);
			lsb = check&0XFF;
			msb = (check >> 8)& 0xFF;
			if((lsb == USART2_RX_BUF[len-2])&&(msb == USART2_RX_BUF[len-1]))
			{
					result = ((USART2_RX_BUF[3]<<24)&0xff000000)|((USART2_RX_BUF[4]<<16)&0x00ff0000)
									 |((USART2_RX_BUF[5]<<8)&0x0000ff00)|(USART2_RX_BUF[6]&0xff);
				
			}
			
			OLED_ShowNum(70,0,result,4,16);
		}
		
		//��������
		{
			if(TIM2->CCR2>=2200)
			{
				TIM2->CCR2=2200;
			}
			if(TIM2->CCR2<=1800)
			{
				TIM2->CCR2=1800;
			}
			
			if(TIM2->CCR1>=2480)
			{
				TIM2->CCR1=2480;
			}
			if(TIM2->CCR1<=2200)
			{
				TIM2->CCR1=2200;
			}
		}
		
}

