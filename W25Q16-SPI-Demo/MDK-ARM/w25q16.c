#include "w25q16.h"
#include <stdio.h>

uint8_t tempbuff[32];
uint8_t address_char[3];
uint8_t read_data[1];
uint8_t i;

HAL_StatusTypeDef WRITE_BYTE(SPI_HandleTypeDef *hspi,uint8_t *write_byte, uint16_t Size,uint32_t address)
{

  for(i=0;i<3;i++)
  {
    address_char[i]=address>>(16-i*8);
  }
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  sprintf((char*)tempbuff,"%c",WRITE_ENABLE);
  HAL_SPI_Transmit(hspi,tempbuff,1,0x10);
	sprintf((char*)tempbuff,"%c",PAGE_PROG);
	HAL_SPI_Transmit(hspi,tempbuff,1,0x10);
  HAL_SPI_Transmit(hspi,address_char,3,0x10);
  HAL_SPI_Transmit(hspi,write_byte,Size,0x10);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
}


HAL_StatusTypeDef READ_BYTE(SPI_HandleTypeDef *hspi,uint8_t *read_byte,uint16_t size,uint32_t address)
{
  for(i=0;i<3;i++)
  {
    address_char[i]=address>>(16-i*8);
  }
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  sprintf((char*)tempbuff,"%c",READ_DATA);
  HAL_SPI_Transmit(hspi,tempbuff,1,0x10);
  for(i=0;i<size;i++)
  {
    HAL_SPI_Receive(hspi,read_byte+i,1,0x10);
  }
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
}

uint32_t READ_JEDECID(SPI_HandleTypeDef *hspi)
{
  uint32_t ID=0;
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  sprintf((char*)tempbuff,"%c",JEDEC_ID);
  HAL_SPI_Transmit(hspi,tempbuff,1,0x10);
  for(i=0;i<3;i++)
  {
    HAL_SPI_Receive(hspi,read_data,1,0x10);
    ID|=read_data[0]<<(16-i*8);
  }
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
  return ID;
}

uint8_t READSR1(SPI_HandleTypeDef *hspi)
{
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  sprintf((char*)tempbuff,"%c",READ_SR1);
  HAL_SPI_Transmit(hspi,tempbuff,1,0x10);
  HAL_SPI_Receive(hspi,read_data,1,0x10);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
  if((read_data[0]&0x01)==1)
    return 1;
  else
    return 0;
}

uint8_t ERASESECTOR(SPI_HandleTypeDef *hspi,uint32_t address)
{
  for(i=0;i<3;i++)
  {
    address_char[i]=address>>(16-i*8);
  }
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  sprintf((char*)tempbuff,"%c",ERASE_SECTOR);
  HAL_SPI_Transmit(hspi,tempbuff,1,0x10);
  HAL_SPI_Transmit(hspi,address_char,3,0x10);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
}




