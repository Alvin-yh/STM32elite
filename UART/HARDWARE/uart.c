#include "uart.h"
#include "stm32f10x.h"

#define MAX_LENGTH 200
char receiveBuffer[MAX_LENGTH]={0};
uint16_t Uart_Status=0;
void uart_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct; 
    USART_InitTypeDef USART_InitSturcture;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
    /**PA9**/
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    /**PA10**/
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /**UART TX**/
    USART_InitSturcture.USART_BaudRate=115200;
    USART_InitSturcture.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitSturcture.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_InitSturcture.USART_Parity=USART_Parity_No;
    USART_InitSturcture.USART_StopBits=USART_StopBits_1;
    USART_InitSturcture.USART_WordLength=USART_WordLength_8b;
    USART_Init(USART1,&USART_InitSturcture);
    /**UART RX**/
    USART_InitSturcture.USART_BaudRate=115200;
    USART_InitSturcture.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitSturcture.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_InitSturcture.USART_Parity=USART_Parity_No;
    USART_InitSturcture.USART_StopBits=USART_StopBits_1;
    USART_InitSturcture.USART_WordLength=USART_WordLength_8b;
    USART_Init(USART1,&USART_InitSturcture);
    
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure);
    USART_Cmd(USART1,ENABLE);
}

void USART1_IRQHandler(void)
{
   u8 res;
    
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        res=USART_ReceiveData(USART1);
        if((res&0x8000)!=0) //get 0x0A 
        {
           Uart_Status|=0x8000; //set bit
        }
        else 
        {
            if((res&0x4000)!=0) //get 0x0D
            {
                Uart_Status|=0x4000; //set bit
                if((res&0x8000)!=0) //get 0x0A
                {
                    Uart_Status|=0x8000;
                }
                else
                {
                    Uart_Status=0; //get wrong , give up receive
                }
            }
            else //not get 0x0D
            {
                if(Uart_Status<MAX_LENGTH)
                {
                   receiveBuffer[Uart_Status]=res;
                   Uart_Status++; 
                }
                
                
            }
            
        }
    }
}
