#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "exti.h"
#include "key.h"
#include "oled.h"
#include "adc.h"

int g_USART1_FLAG =0;
int g_USART3_FLAG =0;

extern u8  TIM5CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ	
int Mode = 0;

u8 string[10] = {0};	//������ǰ��
float pitch =1.2;
int time = 0;
int Distance = 0;


 int main(void)
 {	

	u16 adcx;
	float temp;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    //��ʱ������ʼ��	  
	uart_init(115200);
	uart3_init(115200);
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	TB6612_GPIO_Init();
  EXTIX_Init();
	TCRT5000_Init();
  OLED_Init();
  OLED_Clear();
	SR04_GPIO_Init(); //������PA0
	Adc_Init();		  		//ADC��ʼ��
	 
	TIM3_PWM_Init(999,1439);   //���PWM 
	 
	TIM1_PWM_Init(1999,359); //�����PWM 
	TIM_SetCompare1(TIM1,500);	
	TIM_SetCompare4(TIM1,500);
	
	TIM2_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 
	
	while(1)
	{
		

			//OLED ��ʾADC����
		adcx=Get_Adc_Average(ADC_Channel_4,10);
		temp=(float)adcx*(3.3/4096);
		sprintf((char *)string,"U:%.2f   ",(temp*5));
		OLED_ShowString(12,0,string,16);		
		
		//OLED��ʾ���빦��
		sprintf((char *)string,"D:%d      ",SR04_Distance());
		OLED_ShowString(12,3,string,16);
		
		//OLED��ʾģʽ����
		sprintf((char *)string,"Mode:%d   ",Mode);
		OLED_ShowString(12,6,string,16);
		//�������
		UsartPrintf(USART3,"Mode:%d\r\n",Mode);
		UsartPrintf(USART3,"U:%.2f\r\n",(temp*5));
		UsartPrintf(USART3,"D:%d \r\n",SR04_Distance());
		if(Mode == 0)
		{
			//ֹͣģʽ
			TIM_SetCompare1(TIM3,80);	 //�����ǰ ʹ��������ǰ�� 
			delay_ms(200);
			AIN1 =0;
			AIN2 =0;
			BIN1 =0;
			BIN2 =0;		
		}	
		if(Mode == 3)
		{
					//����������
					TIM_SetCompare1(TIM3,80);	 //�����ǰ ʹ��������ǰ�� 
					delay_ms(200);
					if(SR04_Distance()>25)// ǰ�����ϰ���
					{
							Forward();
							delay_ms(500);
					}
					
					if(SR04_Distance()<25)  //��ǰ���ϰ���
					{
								TIM_SetCompare1(TIM3,50);	 //������ұ�ת��Լ30��
								delay_ms(200);
								if(SR04_Distance()>25)//�Ҳ����ϰ����ж�
								{
										Rightward();
										delay_ms(700);
								}
								else {   //�ұ����ϰ���
										TIM_SetCompare1(TIM3,110); //��������ת��Լ30��
										delay_ms(200);
										if(SR04_Distance()>25)//������ϰ���
										{
													Leftward();
													delay_ms(700);	
										}
										else{
													Backward();//����
													delay_ms(700);
													Rightward(); //��ת
													delay_ms(700);
										}											
							 }
					}					
		}	
		if(Mode == 1)
		{
			//���������
			if(SR04_Distance()>20)
			{
				Forward();
				delay_ms(50);
			}
			if(SR04_Distance()<15)
			{
				Backward();
				delay_ms(50);
			}
			AIN1 =0;
			AIN2 =0;
			BIN1 =0;
			BIN2 =0;		
		}

		if(Mode == 2)
		{
		  //����ң��
			if(g_USART3_FLAG == 5)//ͣ
			{
				LED =~LED;
				AIN1 =0;
				AIN2 =0;
				BIN1 =0;
				BIN2 =0;					
			}
			if(g_USART3_FLAG == 1)//ǰ
			{
				LED =~LED;
				Forward();
				delay_ms(100);
     					
			}
			if(g_USART3_FLAG == 2)//��
			{
				LED =~LED;
				Backward();
				delay_ms(100);
				
			}
			if(g_USART3_FLAG == 3)//��
			{
				LED =~LED;
				Rightward();
				delay_ms(100);	
					
			}
			if(g_USART3_FLAG == 4)//��
			{
				LED =~LED;
				Leftward();
				delay_ms(100);
      
			}
					
		}
		if(Mode == 4)
		{
			
			//����Թ�ѭ��
			if(HW_1 == 0 && HW_2 == 0 && HW_3 == 0 && HW_4 == 0)
			{
				Forward();
				delay_ms(50);
			}
			if(HW_1 == 0 && HW_2 == 1 && HW_3 == 0 && HW_4 == 0)
			{
				Rightward();
				delay_ms(150);
			}
			if(HW_1 == 1 && HW_2 == 0 && HW_3 == 0 && HW_4 == 0)
			{ 
				Rightward();
				delay_ms(250);
			}
			if(HW_1 == 1 && HW_2 == 1 && HW_3 == 0 && HW_4 == 0)
			{
				Rightward();
				delay_ms(300);
			}
			if(HW_1 == 0 && HW_2 == 0 && HW_3 == 1 && HW_4 == 0)
			{
				Leftward();
				delay_ms(150);
			}
			if(HW_1 == 0 && HW_2 == 0 && HW_3 == 0 && HW_4 == 1)
			{
				Leftward();
				delay_ms(250);
			}
			if(HW_1 == 0 && HW_2 == 0 && HW_3 == 1 && HW_4 == 1)
			{
				Leftward();
				delay_ms(300);
			}
		}
	}
 }


