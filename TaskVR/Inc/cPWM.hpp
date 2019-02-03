#ifndef CPWM_HPP_
#define CPWM_HPP_
#include "cTim.hpp"

class cPWM :public cTim
{
public:
	cPWM(TIM_TypeDef *nTim, TIM_Base_InitTypeDef &setupTim, uint32_t Channel):cTim(nTim, setupTim, Channel){}
	~cPWM();
	HAL_StatusTypeDef startPWM();
	void setupPWM(){cTim::setup();}
private:
public:

};


#endif /* CPWM_HPP_ */
