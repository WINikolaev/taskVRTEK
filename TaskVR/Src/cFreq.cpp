#include "cFreq.hpp"



HAL_StatusTypeDef cFreq::startFreq()
{
	return pStart(getHandle(), getChannel());
}


ErrorStatus cFreq::setup_pulseFreq(uint16_t width)
{
return ERROR;
}

