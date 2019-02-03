#ifndef CPWM_HPP_
#define CPWM_HPP_
#include "cTim.hpp"

class cPWM :public cTim
{
public:
	cPWM(TIM_TypeDef *nTim, TIM_Base_InitTypeDef &setupTim, uint32_t Channel):cTim(nTim, setupTim, Channel){}
	~cPWM();
	/* Задаем коэф. заполнения сигнала */
	ErrorStatus virtual setup_pulseWidth(uint16_t width);

	HAL_StatusTypeDef startPWM();
	void setup(){cTim::setup();}

private:
	uint16_t pulseWidthn;
public:

};


#endif /* CPWM_HPP_ */
