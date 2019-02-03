#include "main.h"
#include "adc.h"
#include "dma.h"
#include "iwdg.h"
#include "tim.h"
//#include "cTim.hpp"
#include "cPWM.hpp"
#include "cFreq.hpp"
#include "usart.h"
#include "gpio.h"

void SystemClock_Config(void);
void initPerepherlas(void);

TIM_Base_InitTypeDef setupTim3 = {
		  .Prescaler = 0,
		  .CounterMode = TIM_COUNTERMODE_UP,
		  .Period = 77,
		  .ClockDivision = TIM_CLOCKDIVISION_DIV1
};

TIM_Base_InitTypeDef setupTim2 = {
		  .Prescaler = 0,
		  .CounterMode = TIM_COUNTERMODE_UP,
		  .Period = 77,
		  .ClockDivision = TIM_CLOCKDIVISION_DIV1
};

int main(void)
{
	initPerepherlas();
	//cTim cTim3(TIM3, setupTim3,TIM_CHANNEL_1);
	cPWM *pwmAmplitude = new cPWM(TIM3, setupTim3,TIM_CHANNEL_1);
	cFreq *pwmFrq = new cFreq(TIM2, setupTim2,TIM_CHANNEL_1);
	pwmAmplitude->setup();
	pwmAmplitude->startPWM();
	pwmAmplitude->setup_pulseWidth(38);
	pwmFrq->setupFreq();
	pwmFrq->startFreq();
	pwmFrq->setup_pulseWidth(60);


  while (1)
  {
	  HAL_UART_Transmit_IT(&huart1, (uint8_t*)"str123\r\n", sizeof("str123\r\n"));

	  HAL_IWDG_Refresh(&hiwdg);

	  HAL_Delay(100);
  }
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
