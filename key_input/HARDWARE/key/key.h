#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define KEYUp  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

#define KEY0_Press 1
#define KEY1_Press 2
#define KEYUp_Press 3

void key_Init(void);
uint8_t key_Scan(uint8_t mode);
		 				    
#endif

