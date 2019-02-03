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
	cTim(TIM_TypeDef *nTim, TIM_Base_InitTypeDef &setupTim);
	~cTim();
	void setup();
private:
	TIM_HandleTypeDef htim;
	void cGpio(TIM_HandleTypeDef* Handle);
};




#endif /* CTIM_HPP_ */
