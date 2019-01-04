#include "stm32f10x.h"

void My_USART_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /**open the clock**/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
    /**PA9**/
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    /**PA10**/
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    /**URAT1 TX**/
    USART_InitStructure.USART_BaudRate=115200;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStructure);
    
    /**URAT1 RX**/
    USART_InitStructure.USART_BaudRate=115200;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStructure);
    /**enalbe URAT1**/
    USART_Cmd(USART1,ENABLE);
    /**USART interrupt config**/
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    /**NVIC initial**/
    NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure);
}
void USART1_IRQHandler(void)  //UART interrupt function
{
    u8 res;
    if(USART_GetITStatus(USART1,USART_IT_RXNE))
    {
        res=USART_ReceiveData(USART1);
        USART_SendData(USART1,res);
    }
}

 int main(void)
 {	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  while(1)
  {
   ;
  }
 }
