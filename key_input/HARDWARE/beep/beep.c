#include "beep.h"
#include "stm32f10x_gpio.h"

void beep_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);
}

void beep_On()
{
    GPIO_SetBits(GPIOB,GPIO_Pin_8);
}

