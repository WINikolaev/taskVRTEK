#ifndef CMD_H_
#define CMD_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "microrl.h"
#include "usart.h"
#include "config.h"

extern uint16_t ADC_Data;
extern uint16_t FREQ;
extern uint16_t PULSE_WIDTH;

struct con_cmd_struct{
    uint32_t magic;         /* should always be CMD_MAGIC_HEADER for valid command */
    uint8_t command[16];    /* command name for typing thru terminal */
    uint8_t help[48];       /* short command description */
    void(*callback)(void);  /* callback function to call when command <command> entered */
};

typedef void (*PAuxFunc)(uint32_t value);


void terminal_goto(uint32_t x, uint32_t y);
void terminal_run_aux_task(PAuxFunc pFunc);
static PAuxFunc  pAux = NULL;

typedef struct con_cmd_struct   cmd_tab_t;
void terminal_clear_curline(void);
void terminal_clear(void);
void print(const char *str, uint16_t size);
int execute (int argc, const char * const * argv);
char ** complete(int argc, const char * const * argv);
void sigint (void);

void cmd_show(void);
void con_info(void);
static void aux_info(uint32_t value);


#ifdef __cplusplus
}
#endif

#endif /* CMD_H_ */
