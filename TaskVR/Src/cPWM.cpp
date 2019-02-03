#include "cPWM.hpp"


HAL_StatusTypeDef cPWM::startPWM()
{
	return pStart(getHandle(), getChannel());
}

