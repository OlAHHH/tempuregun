#include "Led_Driver.h"


/***********************************************
**	������ : Led_Init
**	��  �� : ��ʼ��GPIOA�ڵ�8/11/12����			
**  ��  �� : ��
**	����ֵ : ��
************************************************/


void Led_Init(void)
{
	
    /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
    GPIO_InitTypeDef  GPIO_InitStruct;

    /*����RGBLED��ص�GPIO����ʱ��*/
    __HAL_RCC_GPIOA_CLK_ENABLE();

  
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
    GPIO_InitStruct.Pin = REDLED_GPIO_PIN|GREENLED_GPIO_PIN|BLUELED_GPIO_PIN;	

    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;  

    /*��������Ϊ����ģʽ*/
    GPIO_InitStruct.Pull  = GPIO_PULLUP;

    /*������������Ϊ���� */   
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    /*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
    HAL_GPIO_Init(RGBLED_GPIO_PORT, &GPIO_InitStruct);	
		
    /*�ر�RGB��*/
		All_LedOff();

}


/*******************************************
**	������ : Led_Ctl
**	��  �� : ����LED��ɫ��								
**	��  �� : ����1���Ƶ�����  ����2���Ƶ�״̬ 		
**  ����ֵ : ��
********************************************/
void Led_Ctl(LED_Type Led_Type, uint8_t Led_State)
{
	
	switch(Led_Type)
	{
		case Red:
			
			if(Led_State == ON)      //��ƵĿ��ƿ���
			{
				RED_LED(ON);          //��ƿ�
			}else
				RED_LED(OFF);         //��ƹ�
			
		break;
	
		case Green:
			
			if(Led_State == ON)      //��ƵĿ��ƿ���
			{
				GREEN_LED(ON) ;           //�̵ƿ�
			}else
				GREEN_LED(OFF);           //�̵ƹ�
			 
		break;
		
		case Blue:
			
			if(Led_State == ON)      //���ƵĿ��ƿ���
			{
				BLUE_LED(ON);           //���ƿ�
			}else
				BLUE_LED(OFF);         //���ƹ�
			 
		break;
	}
	
}


/*******************************************
**	������ : All_Led_On
**	��  �� : �����еĵ�	�����׵�					
**	��  �� : ��	
**  ����ֵ : ��
********************************************/
void  All_LedOn(void)
{
  RED_LED(ON);           //��ƿ�
	GREEN_LED(ON);           //�̵ƿ�
	BLUE_LED(ON);           //���ƿ�
}
 
/*******************************************
**	������ : All_Led_Off
**	��  �� : �ر����еĵ�	�������					
**	��  �� : ��	
**  ����ֵ : ��
********************************************/
void  All_LedOff(void)
{
  RED_LED(OFF);           //��ƹ�
	GREEN_LED(OFF);           //�̵ƹ�
	BLUE_LED(OFF);           //���ƹ�
}




