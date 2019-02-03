#include "cTim.hpp"



HAL_StatusTypeDef cTim::start()
{
	  //return HAL_TIM_PWM_Start(&this->htim, this->channel);
	return this->pStart(&this->htim, this->channel);
}

void cTim::setup()
{
	  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	  TIM_MasterConfigTypeDef sMasterConfig = {0};
	  TIM_OC_InitTypeDef sConfigOC = {0};

	  if (HAL_TIM_Base_Init(&this->htim) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	  if (HAL_TIM_ConfigClockSource(&this->htim, &sClockSourceConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_TIM_PWM_Init(&this->htim) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	  if (HAL_TIMEx_MasterConfigSynchronization(&this->htim, &sMasterConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	  sConfigOC.Pulse = 0;
	  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	  if (HAL_TIM_PWM_ConfigChannel(&this->htim, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  this->cGpio(&this->htim);
}

void cTim::cGpio(TIM_HandleTypeDef* Handle)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  if(Handle->Instance==TIM2)
	  {
	  /* USER CODE BEGIN TIM2_MspPostInit 0 */

		  /* USER CODE END TIM2_MspPostInit 0 */
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    /**TIM2 GPIO Configuration
	    PA15     ------> TIM2_CH1
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_15;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /* USER CODE BEGIN TIM2_MspPostInit 1 */

	  /* USER CODE END TIM2_MspPostInit 1 */
	  }
	  else if(Handle->Instance==TIM3)
	  {
	  /* USER CODE BEGIN TIM3_MspPostInit 0 */

	  /* USER CODE END TIM3_MspPostInit 0 */

	    __HAL_RCC_GPIOC_CLK_ENABLE();
	    /**TIM3 GPIO Configuration
	    PC6     ------> TIM3_CH1
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_6;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /* USER CODE BEGIN TIM3_MspPostInit 1 */

	  /* USER CODE END TIM3_MspPostInit 1 */
	  }
}

cTim::cTim(TIM_HandleTypeDef &Handle)
{

}

/*Ругается падла, но все равно инициалезирует то что нужно*/
cTim::cTim(TIM_TypeDef *nTim, TIM_Base_InitTypeDef &setupTim, uint32_t Channel) : htim{.Instance = nTim, .Init = setupTim}, channel(Channel)
//cTim::cTim(TIM_TypeDef *nTim, TIM_Base_InitTypeDef &setupTim)
{
	//htim.Instance = nTim;
	//htim.Init = setupTim;
	pStart = HAL_TIM_PWM_Start;
}

cTim::~cTim()
{

}
