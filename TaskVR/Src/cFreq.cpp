#include "cFreq.hpp"



HAL_StatusTypeDef cFreq::startFreq()
{
	return pStart(getHandle(), getChannel());
}


ErrorStatus cFreq::setup_pulseFreq(uint16_t freq)
{
	/*������� ������ ���� �� 16���. ���������� �����...�� ���*/
	if(freq>0 && freq < 16000)
	{
		htim.Instance->ARR = 8000000/freq;
		return SUCCESS;
	}else{
		return ERROR;
	}


}

