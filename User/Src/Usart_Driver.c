#include "Usart_Driver.h"
#include "include.h"


UART_HandleTypeDef UartHandle;
//extern uint8_t ucTemp;  

 /**
  * @brief  DEBUG_USART GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */  
void USARTx_IintConfig(void)
{ 
  
  UartHandle.Instance          = DEBUG_USART;             //ѡ�񴮿�
  
  UartHandle.Init.BaudRate     = DEBUG_USART_BAUDRATE;    //������  115200
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;      //8������λ  
  UartHandle.Init.StopBits     = UART_STOPBITS_1;         //1��ֹͣλ
  UartHandle.Init.Parity       = UART_PARITY_NONE;        //û��У��λ
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;     //û��Ӳ������
  UartHandle.Init.Mode         = UART_MODE_TX_RX;         //����ģʽ
  
  HAL_UART_Init(&UartHandle);                             //��ʼ������
    
 /*ʹ�ܴ��ڽ����ж� */
  __HAL_UART_ENABLE_IT(&UartHandle,UART_IT_RXNE);  
}


/**
  * @brief UART MSP ��ʼ�� 
  * @param huart: UART handle
  * @retval ��
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  DEBUG_USART_CLK_ENABLE();             //�򿪴���ʱ��
	
	DEBUG_USART_RX_GPIO_CLK_ENABLE();     //�򿪽�������ʱ��
  DEBUG_USART_TX_GPIO_CLK_ENABLE();     //�򿪷�������ʱ��
  
/**USART1 GPIO Configuration    
  PA9     ------> USART1_TX
  PA10    ------> USART1_RX 
  */
  /* ����Tx����Ϊ���ù���  */
  GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);
  
  /* ����Rx����Ϊ���ù��� */
  GPIO_InitStruct.Pin = DEBUG_USART_RX_PIN;
  GPIO_InitStruct.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
  HAL_GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct); 
 
  HAL_NVIC_SetPriority(DEBUG_USART_IRQ ,0,1);	//��ռ���ȼ�0�������ȼ�1
  HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ );		    //ʹ��USART1�ж�ͨ��  
}


/*****************  �����ַ��� **********************/
void Usart_SendString(uint8_t *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit(&UartHandle,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
  
}

//�ض���c�⺯��printf������DEBUG_USART���ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
	/* ����һ���ֽ����ݵ�����DEBUG_USART */
	HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}


/*******************************************
**	������ : NVIC_Configuration
**	��  �� : ѡ���жϵ����							
**	��  �� : ��	
**  ����ֵ : ��
********************************************/
void NVIC_Configuration(void)
{
	
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

}


