
#include "cUSART.hpp"


c_usart::c_usart(microrl_t &rl, UART_HandleTypeDef &huart1) : prl(&rl), cmd_husart(&huart1)
{
	MX_USART1_UART_Init();
	//microrl_init(prl, this->print);

}
/*
void c_usart::microrl_init (microrl_t * pThis, void (*print)(const char*))
{
	memset(pThis->cmdline, 0, _COMMAND_LINE_LEN);
	#ifdef _USE_HISTORY
		memset(pThis->ring_hist.ring_buf, 0, _RING_HISTORY_LEN);
		pThis->ring_hist.begin = 0;
		pThis->ring_hist.end = 0;
		pThis->ring_hist.cur = 0;
	#endif
		pThis->cmdlen =0;
		pThis->cursor = 0;
		pThis->execute = NULL;
		pThis->get_completion = NULL;
	#ifdef _USE_CTLR_C
		pThis->sigint = NULL;
	#endif
		pThis->prompt_str = prompt_default;
		pThis->print = print;
	#ifdef _ENABLE_INIT_PROMPT
		//print_prompt (pThis);
	#endif
}
*/
void c_usart::print(const char *str)
{

	for(uint16_t j = 0x00; str[j] != 0; j++)
	{
		while(cmd_husart->gState != HAL_UART_STATE_READY){};
		HAL_UART_Transmit_DMA(cmd_husart, (uint8_t *)&str[j], 1);

	}

}

