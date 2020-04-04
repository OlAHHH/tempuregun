#include "Key_Driver.h"
#include "SysTick_Driver.h"

/***********************************************
**	������ : Led_Init
**	��  �� : ��ʼ��GPIOB�ڵ�12/13/14/15����Ϊ��������	
**  ��  �� : ��
**	����ֵ :	 ��	 
************************************************/
void Key_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;

    /*��������GPIOB�ڵ�ʱ��*/
    ALLKEY_GPIO_CLK_ENABLE();
    
    GPIO_InitStructure.Pin = KEY1_PIN|KEY2_PIN|KEY3_PIN|KEY4_PIN;  //ѡ�񰴼�������
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;                  //��������Ϊ����ģʽ
    GPIO_InitStructure.Pull = GPIO_NOPULL;       							//�������Ų�����Ҳ������
    HAL_GPIO_Init(ALLKEY_GPIO_PORT, &GPIO_InitStructure);     //ʹ������Ľṹ���ʼ������

}


/***********************************************
**	������ : Key_IsAnyButtonPress
**	��  �� : ɨ���������Ұ����Ƿ��а���	
**  ��  �� : ��������ָ�����
**	����ֵ :	 �����Ƿ񱻰���	 
************************************************/
unsigned char Key_IsAnyButtonPress(pen_key_type_t keyType)
{

		/*��ⰴ��1�Ƿ��� */
	if(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT, KEY1_PIN) == KEY_ON )  
	{	 
		//����
		delay_ms(30);
		/*�ٴμ�ⰴ��1�Ƿ��� */
		if(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT, KEY1_PIN) == KEY_ON ) 
		{
//		/*�ȴ������ͷ� */
//		while(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT,KEY1_PIN) == KEY_ON);   

		*keyType = EN_KEY_TYPE_UP;     //�ϰ���
		return 	KEY_ON;	 
		}
	}

			/*��ⰴ��2�Ƿ��� */
	if(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT, KEY2_PIN) == KEY_ON )  
	{	 
		//����
		delay_ms(30);
		/*�ٴμ�ⰴ��2�Ƿ��� */
		if(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT, KEY2_PIN) == KEY_ON ) 
		{
		/*�ȴ������ͷ� */
		while(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT,KEY2_PIN) == KEY_ON);   
			
		*keyType = EN_KEY_TYPE_RIGHT;   //�Ұ���
		return 	KEY_ON;	 
		}
	}
	
	/*��ⰴ��3�Ƿ��� */
	if(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT, KEY3_PIN) == KEY_ON )  
	{	 
		//����
		delay_ms(30);
		/*�ٴμ�ⰴ��3�Ƿ��� */
		if(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT, KEY3_PIN) == KEY_ON ) 
		{
		/*�ȴ������ͷ� */
		while(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT,KEY3_PIN) == KEY_ON);   

		*keyType = EN_KEY_TYPE_LEFT;     //�󰲽�
		return 	KEY_ON;	 
		}
	}
	
	/*��ⰴ��3�Ƿ��� */
	if(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT, KEY4_PIN) == KEY_ON )  
	{	 
		//����
		delay_ms(30);
		/*�ٴμ�ⰴ��3�Ƿ��� */
		if(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT, KEY4_PIN) == KEY_ON ) 
		{
		/*�ȴ������ͷ� */
		while(HAL_GPIO_ReadPin(ALLKEY_GPIO_PORT,KEY4_PIN) == KEY_ON);   

		*keyType = EN_KEY_TYPE_DOWN;     //�󰲽�
		return 	KEY_ON;	 
		}
	}
	

	return KEY_OFF;
}

