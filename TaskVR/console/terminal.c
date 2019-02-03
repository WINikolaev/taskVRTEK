#include "terminal.h"

#include "tskDebug.h"
#include "tskProtocol.h"
#include "microrl.h"

#include "stm32f4xx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aeroimu_cfg.h"
#include "calibration.h"

static void vAuxTask(void *pvParameters);

/* import symbols from linker */
extern const unsigned int Image$$ER_CMD$$Base;
extern const unsigned int Image$$ER_CMD$$Length;

static cmd_tab_t* cmd = (cmd_tab_t*) &Image$$ER_CMD$$Base;
static uint32_t cmd_cnt;

// array for comletion
static char** compl_world;
static microrl_t mrl;

static PAuxFunc  pAux = NULL;
static PAuxInput pInpt = NULL;

//*****************************************************************************
void terminal_print(const char * str){
    debug(str);
}

//*****************************************************************************
// execute callback for microrl library
// do what you want here, but don't write to argv!!! read only!!
int execute (int argc, const char * const * argv){
	int i = 0, j, found;
	// just iterate through argv word and compare it with your commands
	while (i < argc) {
        found = 0;
        for(j =0 ; j < cmd_cnt; j++){
            if (strcmp(argv[i], (const char*)cmd[j].command) == 0){
                cmd[j].callback();
                found = 1;
                break;
            }
        }
        
		if (0 == found) {
			terminal_print ("Command: '");
			terminal_print ((char*)argv[i]);
			terminal_print ("' not found.\n\r");
		}
		i++;
	}
    
	return 0;
}

//*****************************************************************************
// completion callback for microrl library
char ** complete(int argc, const char * const * argv){
	int j = 0;

	compl_world [0] = NULL;

	// if there is token in cmdline
	if (argc == 1) {
		// get last entered token
		char * bit = (char*)argv [argc-1];
		// iterate through our available token and match it
		for (int i = 0; i < cmd_cnt; i++) {
			// if token is matched (text is part of our token starting from 0 char)
			if (strstr((const char*)cmd[i].command, bit) == (const char*)cmd[i].command) {
				// add it to completion set
				compl_world [j++] = (char*)cmd[i].command;
			}
		}
	} else { // if there is no token in cmdline, just terminal_print all available token
		for (; j < cmd_cnt; j++) {
			compl_world[j] = (char*)cmd[j].command;
		}
	}

	// note! last ptr in array always must be NULL!!!
	compl_world [j] = NULL;
	// return set of variants
	return compl_world;
}

//*****************************************************************************
void sigint (void){
	terminal_stop_aux_task();
}

void terminal_run_aux_task(PAuxFunc pFunc){
    pAux = pFunc;
}

void terminal_take_input(PAuxInput pFunc){
    pInpt = pFunc;
}

void terminal_stop_aux_task(void){
    if (NULL != pAux){
        pAux(1);
        terminal_print("\r\n^C catched\r\n");
    }
    
    pAux = NULL;
    pInpt = NULL;
    
    microrl_insert_char(&mrl, '\n');
}

void vAuxTask(void *pvParameters){
    for(;;){
        vTaskDelay(200);
        if (NULL != pAux){
            pAux(0);
        }
    }
}

/**
 * @brief  
 *  this function is called when the debug task was initialized
 *  The function is replace a weak one declarated in tskDebug.c
 */
void debug_on_init(void){
    microrl_init (&mrl, terminal_print);
	// set callback for execute
	microrl_set_execute_callback (&mrl, execute);

    cmd_cnt = (uint32_t) &Image$$ER_CMD$$Length / sizeof(cmd_tab_t);
    
    compl_world = malloc(cmd_cnt * sizeof(char*));
    
	// set callback for completion
	microrl_set_complete_callback (&mrl, complete);

	// set callback for Ctrl+C
	microrl_set_sigint_callback (&mrl, sigint); 
    
    xTaskCreate(vAuxTask, (const char*)"Aux", configMINIMAL_STACK_SIZE * 3, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL);
}

/**
 * @brief  
 *  this function is called when a byte received from DEBUG port
 *  The function replace a weak function, that is in tskDebug.c
 * @params 
 *  chr - received byte
 */
void debug_in_data(uint8_t value){
    if ((NULL != pInpt) && (NULL != pAux)){
        if (value == pInpt(value)){
            microrl_insert_char(&mrl, value);
        }
    }else {
        microrl_insert_char(&mrl, value);
    }
}

void terminal_clear(void){
    terminal_print("\033[2J");    // ESC seq for clear entire screen
    terminal_print("\033[H");     // ESC seq for move cursor at left-top corner
}

void terminal_goto(uint32_t x, uint32_t y){
    char tmp[16];
    sprintf(tmp, "\033[%i;%iH", y, x);    /* set X, Y pos */
    terminal_print(tmp);    
}

void terminal_clear_curline(void){
    terminal_print ("\033[2K");      /* clear line */
}

void con_help (void){
    int32_t i;
    
    terminal_print ("microrl v");
	terminal_print (MICRORL_LIB_VER);
	terminal_print (" AeroIMU debug interface\n\r");
	terminal_print("\n\r");
    
	terminal_print ("Use TAB key for completion\n\rCommand:\n\r");
	
    for(i = 0; i < cmd_cnt; i++){
        terminal_print("\t");
        terminal_print((const char*)cmd[i].command);
        terminal_print("\t - ");
        terminal_print((const char*)cmd[i].help);
    }
}

CON_CMD(help, con_help, "print commands description\n\r");
CON_CMD(clear, terminal_clear, "clear screen\n\r");
