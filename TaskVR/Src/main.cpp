#include "main.h"
#include "adc.h"
#include "dma.h"
#include "iwdg.h"
#include "tim.h"
#include "cUSART.hpp"
#include "cPWM.hpp"
#include "cFreq.hpp"
#include "usart.h"
#include "gpio.h"
#include "microrl.h"
#include "config.h"
#include "cmd.h"

void SystemClock_Config(void);
void initPerepherlas(void);

uint16_t ADC_Data = 0x00;
uint16_t AMPLITUDE = 0x00;
uint16_t FREQ = 0x00;
uint16_t PULSE_WIDTH = 0x00;

extern UART_HandleTypeDef huart1;

microrl_t rl;
microrl_t * prl = &rl;
uint8_t rxData = 0x00;

TIM_Base_InitTypeDef setupTim3 = {
		  .Prescaler = 0,
		  .CounterMode = TIM_COUNTERMODE_UP,
		  .Period = 77,
		  .ClockDivision = TIM_CLOCKDIVISION_DIV1
};

TIM_Base_InitTypeDef setupTim2 = {
		  .Prescaler = 0,
		  .CounterMode = TIM_COUNTERMODE_UP,
		  .Period = 500,
		  .ClockDivision = TIM_CLOCKDIVISION_DIV1
};

int main(void)
{
	initPerepherlas();
	cPWM *pwmAmplitude = new cPWM(TIM3, setupTim3,TIM_CHANNEL_1);
	cFreq *pwmFrq = new cFreq(TIM2, setupTim2,TIM_CHANNEL_1);
	//c_usart *cmd = new c_usart(rl, huart1);
	pwmAmplitude->setup();
	pwmAmplitude->startPWM();
	pwmAmplitude->setup_pulseWidth(38);
	pwmFrq->setupFreq();
	pwmFrq->startFreq();
	pwmFrq->setup_pulseWidth(20);
	pwmFrq->setup_pulseFreq(8000);

	//cmd
	microrl_init (prl, print);
	microrl_set_execute_callback (prl, execute);
	// set callback for completion
	microrl_set_complete_callback (prl, complete);
	// set callback for Ctrl+C
	microrl_set_sigint_callback (prl, sigint);
	HAL_UART_Receive_IT(&huart1, &rxData, sizeof(rxData));

	con_info();
  while (1)
  {
	  /*хз почему он в непрерывном режиме перестал работать....будем дергать вручную раз такое дело*/
	  HAL_ADC_Start_DMA(&hadc3,(uint32_t*) &ADC_Data,1);
	  if(pAux != NULL){pAux(0);};
	  AMPLITUDE = pwmAmplitude->getPulseWidth();
	  FREQ = pwmFrq->getPulseFreq();
	  PULSE_WIDTH = pwmFrq->getPulseWidth();
	  cmd_show();

	  //u = ((float)ADC_Data)*3/4096;
	  //sprintf(str,"%.2f",u);
	  HAL_Delay(100);
	  //print("Board information:\n\r");
	  //HAL_UART_Transmit_IT(&huart1, (uint8_t*)"\033[2K", sizeof("\033[2K"));
	  HAL_IWDG_Refresh(&hiwdg);
	  HAL_UART_Receive_IT(&huart1, &rxData, sizeof(rxData));


  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	microrl_insert_char(prl, rxData);
	//HAL_UART_Transmit_DMA(&huart1, &rxData, sizeof(rxData));
	//print((const char *)&rxData,1);
	HAL_UART_Receive_IT(&huart1, &rxData, sizeof(rxData));
}


void initPerepherlas(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_USART1_UART_Init();
	MX_ADC3_Init();
	//MX_TIM3_Init();
	//MX_TIM2_Init();
	MX_TIM4_Init();
	MX_TIM5_Init();
	//MX_IWDG_Init();
	//HAL_ADC_Start(&hadc3);

}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
