#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__


#include "stm32f1xx.h"
#include "main.h"


 /** �������±��ú�
	* ��������Ϊ�͵�ƽ������ KEY_ON = 0�� KEY_OFF = 1
	* ����������Ϊ�ߵ�ƽ���Ѻ����ó�KEY_ON = 1��KEY_OFF = 0 ����
	*/
#define KEY_ON	0
#define KEY_OFF	1

//���Ŷ���
/*******************************************************/
#define KEY1_PIN                  GPIO_PIN_15  
#define KEY2_PIN                  GPIO_PIN_14     
#define KEY3_PIN                  GPIO_PIN_13      
#define KEY4_PIN                  GPIO_PIN_12      

#define ALLKEY_GPIO_PORT            GPIOB                      
#define ALLKEY_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()  
/*******************************************************/



typedef enum en_key_type
{
	EN_KEY_TYPE_MENU = 0,
	EN_KEY_TYPE_UP,
	EN_KEY_TYPE_DOWN,
	EN_KEY_TYPE_LEFT,
  EN_KEY_TYPE_RIGHT,
	EN_KEY_TYPE_NONE,

} en_key_type_t, *pen_key_type_t;


void Key_Init(void);
unsigned char Key_IsAnyButtonPress(pen_key_type_t keyType);

#endif /* ____KEY_DRIVER_H */



