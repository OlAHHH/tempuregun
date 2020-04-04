#ifndef __BEEP_DRIVER_H_
#define __BEEP_DRIVER_H_

#include "stm32f1xx.h"
#include "main.h"

/* �궨�� */
#define GENERAL_TIMx                        TIM3
#define GENERAL_TIM_RCC_CLK_ENABLE()        __HAL_RCC_TIM3_CLK_ENABLE()
#define GENERAL_TIM_RCC_CLK_DISABLE()       __HAL_RCC_TIM3_CLK_DISABLE()
#define GENERAL_TIM_GPIO_RCC_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE();

#define GENERAL_TIM_CH4_PORT                GPIOB
#define GENERAL_TIM_CH4_PIN                 GPIO_PIN_1

#define GENERAL_TIM_IRQn                    TIM3_IRQn
#define GENERAL_TIM_IRQHANDLER              TIM3_IRQHandler

// ���嶨ʱ��Ԥ��Ƶ
#define GENERAL_TIM_PRESCALER               719  // ʵ��ʱ��Ƶ��Ϊ��36kHz
// ���嶨ʱ������
#define GENERAL_TIM_PERIOD                  100


extern TIM_HandleTypeDef htimx;

void Beep_Init(void);
void Beep_VoiceRegulation(uint8_t VoiceSize);

#endif /* __BEEP_DRIVER_H */






