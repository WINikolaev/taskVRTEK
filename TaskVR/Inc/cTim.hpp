/*
 * cTim.hpp
 *
 *  Created on: 3 ����. 2019 �.
 *      Author: User
 */

#ifndef CTIM_HPP_
#define CTIM_HPP_
#include "main.h"


class cTim
{
public:
	cTim(TIM_HandleTypeDef &Handle);
	cTim(TIM_TypeDef *nTim, TIM_Base_InitTypeDef &setupTim, uint32_t Channel);
	~cTim();
	void setup();
	HAL_StatusTypeDef start();
private:
	TIM_HandleTypeDef htim;
	uint32_t channel;
	void cGpio(TIM_HandleTypeDef* Handle);
	/*��������� �� ������� ������ ����*/
	HAL_StatusTypeDef (*funcStart)(TIM_HandleTypeDef *htim, uint32_t Channel);
};




#endif /* CTIM_HPP_ */
