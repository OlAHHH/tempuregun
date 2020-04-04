#include "Beep_Driver.h"


/* ˽�����Ͷ���*/
TIM_HandleTypeDef htimx;

/**
  * ��������: ��ʱ��Ӳ����ʼ������
  * �������: htim����ʱ���������ָ��
  * �� �� ֵ: ��
  * ˵    ��: �ú�����GENERAL_TIMx_Init��������
  */
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim->Instance==GENERAL_TIMx)
  {  
    /* ��ʱ��ͨ���������Ŷ˿�ʱ��ʹ�� */
    GENERAL_TIM_GPIO_RCC_CLK_ENABLE();

    /* ��ʱ��ͨ��3��������IO��ʼ�� */
    GPIO_InitStruct.Pin = GENERAL_TIM_CH4_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GENERAL_TIM_CH4_PORT, &GPIO_InitStruct);
  }
}

/**
  * ��������: ͨ�ö�ʱ����ʼ��������ͨ��PWM���
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void Beep_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  
  htimx.Instance = GENERAL_TIMx;
  htimx.Init.Prescaler = GENERAL_TIM_PRESCALER;
  htimx.Init.Period = GENERAL_TIM_PERIOD;
	htimx.Init.CounterMode = TIM_COUNTERMODE_UP;
  htimx.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htimx);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htimx, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htimx, &sMasterConfig);
  
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.Pulse = 0;
  HAL_TIM_PWM_ConfigChannel(&htimx, &sConfigOC, TIM_CHANNEL_4);

  HAL_TIM_MspPostInit(&htimx);
	
	HAL_TIM_PWM_Start(&htimx, TIM_CHANNEL_4);//ͨ��4��ʼ����PWM�ź�
}

/**
  * ��������: ������ʱ��Ӳ����ʼ������
  * �������: htim_base��������ʱ���������ָ��
  * �� �� ֵ: ��
  * ˵    ��: �ú�����HAL���ڲ�����
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==GENERAL_TIMx)
  {
    /* ������ʱ������ʱ��ʹ�� */
    GENERAL_TIM_RCC_CLK_ENABLE();
    
    /* ���ö�ʱ���ж����ȼ���ʹ�� */
    HAL_NVIC_SetPriority(GENERAL_TIM_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(GENERAL_TIM_IRQn);
  }
}

/**
  * ��������: ������ʱ��Ӳ������ʼ������
  * �������: htim_base��������ʱ���������ָ��
  * �� �� ֵ: ��
  * ˵    ��: �ú�����HAL���ڲ�����
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==GENERAL_TIMx)
  {
    /* ������ʱ������ʱ�ӽ��� */
    GENERAL_TIM_RCC_CLK_DISABLE();
    /* ���ö�ʱ���ж� */
    HAL_NVIC_DisableIRQ(GENERAL_TIM_IRQn);
  }
} 


/*******************************************
**	������ : Beep_VoiceRegulation
**	��  �� : ���Ʒ�������������С						
**	��  �� : ���ֵ������200����Сֵ��С��0��������		
**  ����ֵ : ��
********************************************/
void Beep_VoiceRegulation(uint8_t VoiceSize)
{

	TIM3-> CCR4 = VoiceSize;

}


