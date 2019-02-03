#include "cPWM.hpp"


HAL_StatusTypeDef cPWM::startPWM()
{
	return pStart(getHandle(), getChannel());
}

ErrorStatus cPWM::setup_pulseWidth(uint16_t width)
{
	/*если скважность в переделаз  от 90% периода и 10% то все ок*/
	if(width < ((4 * htim.Init.Period)/5) && width > (htim.Init.Period/10))
	{
		htim.Instance->CCR1 = width;
		return SUCCESS;
	}else{
		htim.Instance->CCR1 = htim.Init.Period/10;
		return ERROR;
	}
}
