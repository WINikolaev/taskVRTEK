
#ifndef CUSART_HPP_
#define CUSART_HPP_

#define cmd_print(str) HAL_UART_Transmit_DMA(&huart1, (uint8_t *)str, sizeof(str))

#include "main.h"
#include "microrl.h"
#include "usart.h"
#include "config.h"
#include "cstring"


extern UART_HandleTypeDef huart1;
extern char * prompt_default;

class c_usart
{
public:
	c_usart(microrl_t &rl, UART_HandleTypeDef &huart1);
	~c_usart(){};
	void print(const char *str);
	void microrl_init (microrl_t * pThis, void (*print)(const char*));
private:
	microrl_t *prl;
	UART_HandleTypeDef *cmd_husart;
protected:

};


#endif

