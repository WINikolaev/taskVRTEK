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


	HAL_StatusTypeDef start();
private:
	void cGpio(TIM_HandleTypeDef* Handle);


protected:
	void virtual setup();
	TIM_HandleTypeDef htim;
	uint32_t channel;
	/*��������� �� ������� ������ ����*/
	HAL_StatusTypeDef (*pStart)(TIM_HandleTypeDef *htim, uint32_t Channel);
	TIM_HandleTypeDef *getHandle(){return &htim;}
	uint32_t getChannel(){return channel;}
};




#endif /* CTIM_HPP_ */
