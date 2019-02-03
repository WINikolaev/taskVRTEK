#include "cmd.h"


static cmd_tab_t* cmd;
static uint32_t cmd_cnt;


static char** compl_world;


void print(const char *str, uint16_t size)
{
	//HAL_UART_Transmit_DMA(&huart1, (uint8_t *)str, size);
	HAL_UART_Transmit(&huart1, (uint8_t *)str, size,0xFFFF);
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
				print ("Command: '", sizeof("Command: '"));
				print ((char*)argv[i],sizeof(argv[i]));
				print ("' not found.\n\r", sizeof("' not found.\n\r"));
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


void sigint (void)
{
	print ("^C catched!\n\r", sizeof("^C catched!\n\r"));
	//print ("catched!\r\n");
}
void terminal_clear(void){
    print("\033[2J", sizeof("\033[2J"));    // ESC seq for clear entire screen
    //HAL_UART_Transmit_DMA(&huart1, (uint8_t*)"\033[2J", sizeof("\033[2J"));
    print("\033[H", sizeof("\033[H"));     // ESC seq for move cursor at left-top corner
    //HAL_UART_Transmit_DMA(&huart1, (uint8_t*)"\033[H", sizeof("\033[H"));
}

void terminal_run_aux_task(PAuxFunc pFunc){
    pAux = &pFunc;
}

void terminal_clear_curline(void)
{
	print ("\033[2K",sizeof("\033[2K"));
}

void terminal_goto(uint32_t x, uint32_t y)
{
	char tmp[16];
	uint16_t size = sprintf(tmp, "\033[%i;%iH", y, x);    /* set X, Y pos */
	print(tmp,size);
}

void aux_info(uint32_t value)
{
	terminal_clear();
	print("aux\r\n",sizeof("aux\r\n"));

}

void con_info(void){
    terminal_clear();
    print ("info: \n\r", sizeof("info: \n\r"));
    print ("Amplitude\t Frequency\t Pulse width\t\r\n", sizeof("Amplitude\t Frequency\t pulse width\t\r\n"));
    //terminal_run_aux_task(aux_info);
}


void cmd_show()
{
	//terminal_clear();
	terminal_goto(0, 3);
	terminal_clear_curline();
	char str[128];
	float u = ((float)ADC_Data)*3/4096;
	uint16_t size = sprintf(str,"%.2f\t\t %i\t\t %i\t\t",u, FREQ, PULSE_WIDTH);

	print(&str,size);
}


