#include "cmd.h"


static cmd_tab_t* cmd;
static uint32_t cmd_cnt;


static char** compl_world;

void print(const char *str)
{
	for(uint16_t j = 0x00; str[j] != 0; j++)
	{
		while(huart1.gState != HAL_UART_STATE_READY){};
		HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&str[j], 1);
	}
}



int execute (int argc, const char * const * argv)
{
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
				print ("Command: '");
				print ((char*)argv[i]);
				print ("' not found.\n\r");
			}
			i++;
		}

		return 0;
}

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

