#ifndef __MLX90614_DRIVER_H_
#define __MLX90614_DRIVER_H_


#include "stm32f1xx.h"
#include "main.h"
#include "stdint.h"



//#define ACK           0
//#define NACK          1
//#define SA            0x00 //Slave address ����MLX90614ʱ��ַΪ0x00,���ʱ��ַĬ��Ϊ0x5a
//#define RAM_ACCESS    0x00 //RAM access command
//#define EEPROM_ACCESS 0x20 //EEPROM access command
//#define RAM_TOBJ1     0x07 //To1 address in the eeprom



void SMBus_StartBit(void);
void SMBus_StopBit(void);
void SMBus_SendBit(uint8_t);
uint8_t SMBus_SendByte(uint16_t);
uint8_t SMBus_ReceiveBit(void);
uint8_t SMBus_ReceiveByte(uint8_t);
void SMBus_Delay(uint16_t);
void SMBus_Init(void);

uint16_t SMBus_ReadMemory(uint8_t, uint8_t);
uint8_t PEC_Calculation(uint8_t*);
float SMBus_ReadTemp(void); //��ȡ�¶�ֵ


#endif



