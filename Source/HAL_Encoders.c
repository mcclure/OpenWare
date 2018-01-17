#include "stm32f4xx_hal.h"
#include "HAL_Encoders.h"

#include <string.h>

SPI_HandleTypeDef* Encoders_SPIConfig;
 
// Variables
#define STATE_Idle				0
#define STATE_ContConv		1
#define STATE_Busy				1

#define TASK_readADC			0
#define TASK_setDAC				1

// SPI Read/Write bit
#define SPI_Read        	1
#define SPI_Write       	0

// Pin Control
#define pbarCS(state)		HAL_GPIO_WritePin(ENC_nCS_GPIO_Port,  ENC_nCS_Pin,  (GPIO_PinState)state)

uint16_t rgENC_Values[7];
	 
//_____ Functions _____________________________________________________________________________________________________
// Port and Chip Setup
void Encoders_readAll(void)
{ 
	uint16_t x  = 130;
	
	pbarCS(0);
	while(--x){__NOP();}																									// *** The minimum NOP delay for proper operation seems to be 130 ***
	HAL_SPI_Receive(Encoders_SPIConfig, (uint8_t*)rgENC_Values, 14, 100);
	pbarCS(1);
}

void Encoders_readSwitches(void)
{ 
	uint16_t x  = 130;
	
	pbarCS(0);
	while(--x){__NOP();}
	HAL_SPI_Receive(Encoders_SPIConfig, (uint8_t*)rgENC_Values, 1, 100);
	pbarCS(1);
}


//_____ Initialisaion _________________________________________________________________________________________________
void Encoders_init (SPI_HandleTypeDef *spiconfig)
{
	Encoders_SPIConfig = spiconfig;
}

