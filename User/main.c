/******************************��ӭ��ҽ��� ��о֪ʶѧ�á� *********************************
**
**
**	
**	     �m    ��  �� .�m                        							��  ���ߣ���Ҷ��     
**	****�� �� /��\/��\ �m ��****                   						�ﵥƬ��&���ؼ���QQȺ�� 82558344 ��        
**	 ����    ����� ��㣮������Oooo          ��      		��������&Ƕ��ʽȺQQȺ: 544101253 ��
**	 �|�}�~�����������~�}�|�z�y���m�y�z�|�}    __�x�y�z�x__ ��     ��΢��Ⱥ��Ⱥ���ύ����:  ��ȡ��Կ��
										                    ^                                       |
																																								|
																														���ÿ���Ƥ��ǧƪһ�ɣ����ϵĴ�����һ��һ
																																�з�������������ţ��޾���ѧʶ����ɳ���

��ѧ���ߵ��ǿ�Դ���·�ߡ��������е�ԭ���������¡��鼮����Ƶ������ѻ�ȡ������
                       ��ѧ�����ѣ���ª�����ţ�
										      ��ͬѧϰ����������
********************************************************************************************/

#include "include.h"
#include <stdio.h>
#include "bmp.h"

//�¶ȵĵ�λ ��
uint8_t TempCompany[][16]=
{
	0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,
	0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00,/*"��",0*/

};

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	uint8_t i,j;
	
	 en_key_type_t keyType;    //�������ͱ���
	 float Temperature = 0;    //�¶����ݱ����������ͣ�
	 char TempValue[80] = {0}; //�¶�ֵ���ַ�����
	 char VoltageValueStr[80] = {0}; //��ѹֵ���ַ�����
	 uint32_t TempCleanScreenFlag = 0;  //�¶������ı�־
	 uint32_t VolCleanScreenFlag = 0;  //��ѹ�����ı�־
	 uint8_t CollectionFlag = 0;  //�ɼ����ݵı�־
	 float VoltageValue = 0.0;     //Vsimple��ѹֵ����
	 float VBAT = 0.0;            //﮵�ص�ѹ�ı���ֵ
	 
	 HAL_Init();      
   SystemClock_Config();    // ϵͳʱ�ӳ�ʼ����72 MHz 
	 NVIC_Configuration();    //�ж�����ѡ��
	 Led_Init();              //��ʼ��RGB��
	 SysTick_Init();          //SYSTick�ĳ�ʼ��
	 USARTx_IintConfig();     //����1�ĳ�ʼ��
	 Key_Init();              //������ʼ��
	 Beep_Init();             //��������ʼ��
	 OLED_Init();			          //��ʼ��OLED��ʾ��
   Voltage_Init();          //��ѹ�ɼ���ʼ��
	 SMBus_Init();             //��ʼ��
	
//	//�����޲�������	
	OLED_DrawBMP(0,0,128,8,Peacock);
	  
	while(1)
	{

		if(Key_IsAnyButtonPress(&keyType) == KEY_ON)    //����ɨ��
		{
		
			switch((uint8_t)keyType)
			{
				
				//�ϰ���:  ʵ�ֲ��¹��ܣ��ɼ�MLX90614�����ݣ�������ʾ����ʾ
				case EN_KEY_TYPE_UP:            //�ϰ���
					
							if(CollectionFlag != 0)
							{
								
								//�����ģʽ��ֻ��һ����
								if(TempCleanScreenFlag == 0)
								{
									OLED_DataClear() ;
									
									TempCleanScreenFlag++;
								}
								
								//�¶ȵ�λ��ʾ ���棩
								for(i = 5;i < 6;i++)
								{
									j = i - 5;
									OLED_ShowCHinese16x16(i*16,2,j,TempCompany);			
								}
							
								Temperature = SMBus_ReadTemp();  //��ȡ�¶�  	
								sprintf(TempValue,"%.1f", Temperature);     //������ת�����ַ���
								OLED_ShowString(40,2,(uint8_t *)TempValue,16);   //��ʾ�¶�
								
								//���ȷ�Ϊ�� ���� ��37.2��38�棻�еȶ��ȣ�38��1��39�棺���ȣ�39��1��41�棻 ������ ��41������
								//����Ԥ��
								if(Temperature >= 37.2 && Temperature <= 38.0)
								{
									  //���Ⱥͺ��Ԥ��
										for(i = 0;i < 5;i++)
										{
											Beep_VoiceRegulation(10);
											 Led_Ctl( Red, ON );
											delay_ms(500);
											
											Beep_VoiceRegulation(0);	
											Led_Ctl( Red, OFF );
											delay_ms(500);
										}
								}
								//����Ԥ��
								else if(Temperature >= 38.1 && Temperature <= 39.0)
								{
										for(i = 0;i < 5;i++)
										{
											 Beep_VoiceRegulation(10);
											 Led_Ctl( Red, ON );
											 delay_ms(300);
											 Beep_VoiceRegulation(0);
											 Led_Ctl( Red, OFF );
											 delay_ms(300);
											}
								}
							  
								//����Ԥ��
								else if(Temperature >= 39.1 && Temperature <= 41.0)
								{
										for(i = 0;i < 5;i++)
									 {
												
											Beep_VoiceRegulation(10);
											Led_Ctl( Red, ON );
											delay_ms(80);
											Beep_VoiceRegulation(0);
											Led_Ctl( Red, OFF );
											delay_ms(80);
										}
								}
								//������Ԥ��
								else if(Temperature > 41)
								{
											for(i = 0;i < 5;i++)
											{
										     Beep_VoiceRegulation(10);
												 Led_Ctl( Red, ON );
										     delay_ms(50);
										     Beep_VoiceRegulation(0);
												 Led_Ctl( Red, OFF );
										     delay_ms(50);
											}
								}
								
								VolCleanScreenFlag = 0; //�����ѹ�����ı�־
							}

				break;
				
							
				//�°���:  ʵ�ֲɼ���ѹ���ܣ�������ʾ����ʾ
				case EN_KEY_TYPE_DOWN:         //�°���
					
						if(CollectionFlag != 0)
						{	
								//�����ģʽ��ֻ��һ����
								if(VolCleanScreenFlag == 0)
								{
									OLED_DataClear() ;      //��������е���Ļ��Ϣ
									OLED_ShowChar(80,2,'V',16);
									VolCleanScreenFlag++;
									
								}
								
								
								VoltageValue = Get_VoltageValue();
								//���ڰ����ڵ�ѹ�ɼ��ĵ�·�м����˵��裬�����ڴ�����·�У������𵽵�������:��ѹ
								//�ʣ�﮵�صĵ�ѹ VBAT = VoltageValue*��10 K + 10K��/10K

								VBAT = VoltageValue*(10 + 10)/10;
								
								sprintf(VoltageValueStr,"%.2f", VBAT);     //������ת�����ַ���
								//���ڰ����ڵ�ѹ�ɼ��ĵ�·�м����˵������Լ�1.2V
								sprintf(VoltageValueStr,"%.2f", (VoltageValue + 1.20));     //������ת�����ַ���
								OLED_ShowString(40,2,(uint8_t *)VoltageValueStr,16);   //��ʾ�¶�
								
								//��ѹԤ��
								if(VoltageValue < 1.5)
								{
											for(i = 0;i < 5;i++)   //��˸5��
											{
													Beep_VoiceRegulation(10);    //������ʾ
												  Led_Ctl( Green, ON );
													delay_ms(800);               //�̵�
													Beep_VoiceRegulation(0);
												  Led_Ctl( Green, OFF );
													delay_ms(800);
										 }
								}
								
								TempCleanScreenFlag = 0;    //����¶���ʾ�ı�־
						}
				break;
				
				
				//��������к��ˣ�����ʾ�׽���
				case EN_KEY_TYPE_LEFT:    
					
				  delay_us(10); 
					OLED_Clear();  //����
					delay_ms(500);   //��ʱ500ms
					OLED_DrawBMP(0,0,128,8,Peacock);  //��ʾ�׽���
				
					CollectionFlag = 0;  //�ɼ���־���
					TempCleanScreenFlag	 = 0; //��ձ�־
				  VolCleanScreenFlag = 0; //��ձ�־
						
				break;
				
				
				//����ѡ�����
				case  EN_KEY_TYPE_RIGHT:

					OLED_Clear();  //����
					delay_ms(500);   //��ʱ500ms
					OLED_DrawBMP(0,0,128,8,BMP1);  //��ʾ�׽���
						
				 OLED_ShowString(0,2,"(T):up (V):dowm ",16);   //��ʾ�¶�
					
				 CollectionFlag++;  //�ɼ���־λ++
				 TempCleanScreenFlag	 = 0; //��ձ�־
				VolCleanScreenFlag = 0; //��ձ�־
				break;
				
				default :				
					  ;			
			}
		}
		
	}
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 1
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  oscinitstruct.HSEState        = RCC_HSE_ON;
  oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
}


/************************ *****END OF FILE*****************************************/
