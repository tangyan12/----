#include "led.h"



/**
* @brief ��ʼLED ����PC13
* @param 
* @return 
*/
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC13�˿�ʱ��
	

	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //PC13 �˿�����, �������
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOC,GPIO_Pin_13); 						 //PC13 ����� 
}
/**
* @brief ��ʼTB6612�� AIN1 AIN2 BIN1 BIN2
* @brief ����AIN1--PB13 AIN2-PB12
						 BIN1--PB1  BIN2--PB0
* @param 
* @return 
*/
void TB6612_GPIO_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_1|GPIO_Pin_0;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_1|GPIO_Pin_0); 						 //PE.5 ����� 
}
/**
* @brief ������SR04Trig GPIO��ʼ�� 
* @param 
* @return 
*/
void SR04_GPIO_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //PA0�˿�����, �������
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOA,GPIO_Pin_0);
}
/**
* @brief ��ǰ����ʱ
* @param 
* @return 
*/
void Forward(void)
{
		AIN1 =1;
		AIN2 =0;
		BIN1 =1;
		BIN2 =0;
		TIM_SetCompare1(TIM1,1500);	 
	  TIM_SetCompare4(TIM1,1500);

}	
/**
* @brief �������ʱ
* @param 
* @return 
*/
void Backward(void)
{
		AIN1 =0;
		AIN2 =1;
		BIN1 =0;
		BIN2 =1;
		TIM_SetCompare1(TIM1,1500);	 
	  TIM_SetCompare4(TIM1,1500);

}	
/**
* @brief ��������ʱ
* @param 
* @return 
*/
void Rightward(void)
{
		AIN1 =1;
		AIN2 =0;
		BIN1 =0;
		BIN2 =1;
		TIM_SetCompare1(TIM1,1500);	 
	  TIM_SetCompare4(TIM1,1500);

}	
/**
* @brief ��������ʱ
* @param 
* @return 
*/
void Leftward(void)
{
		AIN1 =0;
		AIN2 =1;
		BIN1 =1;
		BIN2 =0;
		TIM_SetCompare1(TIM1,1500);	 
	  TIM_SetCompare4(TIM1,1500);

}	

  
