#ifndef CFREQ_HPP_
#define CFREQ_HPP_
#include "cTim.hpp"
#include "cPWM.hpp"

class cFreq :public cPWM
{
public:
	cFreq(TIM_TypeDef *nTim, TIM_Base_InitTypeDef &setupTim, uint32_t Channel):cPWM(nTim, setupTim, Channel){}
	~cFreq();
	/* Задаем коэф. заполнения сигнала */
	ErrorStatus setup_pulseFreq(uint16_t freq);
	ErrorStatus setup_pulseWidth(uint16_t width){return cPWM::setup_pulseWidth(width);};
	HAL_StatusTypeDef startFreq();
	void setupFreq(){cTim::setup();}
	/*Простите за эту херю...но час ночи сказывается...*/
	uint16_t getPulseFreq(){return 8000000/(htim.Instance->ARR);};
	uint16_t getPulseWidth(){return htim.Instance->CCR1;};

private:
	uint16_t pulseWidthn;
public:

};


#endif /* CFREQ_HPP_ */
