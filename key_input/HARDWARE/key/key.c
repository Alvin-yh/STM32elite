#include "key.h"
#include "stm32f10x.h"
#include "delay.h"



void key_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
    /**key0 and key1 initial**/
    
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    /**key up initial**/
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
}

uint8_t key_Scan(uint8_t mode)
{
   static uint8_t key_up=1;
   if(mode)
   {
      key_up=1; 
   }
   if(key_up&&(KEY0==0||KEY1==0||KEYUp==1))
   {
       delay_ms(10);
       key_up=0;
       if(KEY0==0)
       {
           return KEY0_Press;
       }
       else if(KEY1==0)
       {
           return KEY1_Press;
       }
       else if(KEYUp==1)
       {
           return KEYUp_Press;
       }
   }
   else if(KEY0==1&&KEY1==1&&KEYUp==0) 
   {
       key_up=1;
   }
   return 0;
}


