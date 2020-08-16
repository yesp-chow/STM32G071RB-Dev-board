#ifndef __W25Q16_H
#define __W25Q16_H
#endif

#include "main.h"
#include "spi.h"
#include "gpio.h"

#define DUMMY                 0xFF
#define WRITE_ENABLE          0x06
#define WRITE_DISABLE         0x04
#define DEVICE_ID             0x90
#define JEDEC_ID              0x9F
#define READ_SR1              0x05
#define READ_SR2              0x35
#define READ_SR3              0x15
#define ERASE_SECTOR          0x20
#define ERASE_32BLOCK         0x52
#define ERASE_64BLOCK         0xD8
#define ERASE_CHIP            0x60
#define READ_DATA             0x03
#define FAST_READ             0x0B
#define PAGE_PROG             0x02
#define POWER_DOWN            0xB9
#define ENABLE_RESET          0x66
#define RESET_DEVICE          0x99


HAL_StatusTypeDef WRITE_BYTE(SPI_HandleTypeDef *hspi,uint8_t *write_byte, uint16_t size,uint32_t address);    //Write several bytes
HAL_StatusTypeDef READ_BYTE(SPI_HandleTypeDef *hspi,uint8_t *read_byte,uint16_t size,uint32_t address);       //Read several bytes
uint8_t ERASESECTOR(SPI_HandleTypeDef *hspi,uint32_t address);                                                //ERASE SECTOR
uint32_t READ_JEDECID(SPI_HandleTypeDef *hspi);                                                               //READ JEDECID
uint8_t READSR1(SPI_HandleTypeDef *hspi);                                                                     //Read the value of the status register 1