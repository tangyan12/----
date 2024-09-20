#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	


#define LED PCout(13)// PE5	

#define AIN1 PBout(13)// PE5	
#define AIN2 PBout(12)// PE5	
#define BIN1 PBout(1)// PE5	
#define BIN2 PBout(0)// PE5	

#define SR04 PAout(0)





void LED_Init(void);//³õÊ¼»¯


void TB6612_GPIO_Init(void);
void Forward(void);
void Backward(void);
void Rightward(void);
void Leftward(void);
void SR04_GPIO_Init(void);//³¬Éù²¨PA0

		 				    
#endif
