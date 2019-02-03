#include "terminal.h"
#include "stm32f4xx.h"

static void con_reboot(void){
    NVIC_SystemReset();
}

CON_CMD(sys_reboot, con_reboot, "reboot IMU\n\r");
