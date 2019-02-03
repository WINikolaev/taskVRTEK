#include "terminal.h"
#include "aeroimu_cfg.h"
#include "calibration.h"
#include "sb_structs.h"

#include <stdio.h>


static void con_info(void)
{
    char str[128];
    uint32_t id[3];
    extern const volatile CSWInfo swi;
    
    sprintf(str, "\tCalibration:\t%s\n\r", CAL_ERROR_OK == calPresent() ? "yes" : "no");
    terminal_print(str);
    
    sprintf(str, "\tAeroID: \t%08X%08X%08X\n\r", ((uint32_t*)0x1FFF7A10)[0], ((uint32_t*)0x1FFF7A10)[1], ((uint32_t*)0x1FFF7A10)[2]);
    terminal_print(str);
    
    if (CAL_ERROR_OK == calPresent()){
        calGetID(id);
        sprintf(str, "\tCalibID:\t%08X%08X%08X\n\r", id[0], id[1], id[2]);
        terminal_print(str);
    }
    
    sprintf(str, "\tFirmware:\tv%02X.%02X\n\r", 0xFF & (swi.uiFirmwareVer >> 8), 0xFF & swi.uiFirmwareVer);
    terminal_print(str);
    sprintf(str, "\tBuild at:\t%s\n\r", (char*)swi.uiBuldDate);
    terminal_print(str);
    
    sprintf(str, "\tBoard: \tv%02X.%02X\n\r", 0xFF & (swi.uiHardwareVer >> 8), 0xFF & swi.uiHardwareVer);
    terminal_print(str);
    
    terminal_print("\tCPU: \tSTM32F417VG, ARM Cortex-M4F\r\n");
    sprintf(str, "\tSYSCLK \t%iMHz, HCLK %iMHz, APB1 %iMHz, APB2 %iMHz\n\r", 
                                             clk_get(CLK_SYSCLK) / 1000000, 
                                             clk_get(CLK_HCLK)   / 1000000,
                                             clk_get(CLK_APB1)   / 1000000,
                                             clk_get(CLK_APB2)   / 1000000);
    terminal_print(str);
}

CON_CMD(info, con_info, "show IMU info\n\r");
