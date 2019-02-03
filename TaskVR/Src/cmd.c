#include "cmd.h"


void print(const char *str)
{
	for(uint16_t j = 0x00; str[j] != 0; j++)
	{
		while(huart1.gState != HAL_UART_STATE_READY){};
		HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&str[j], 1);
	}
}
