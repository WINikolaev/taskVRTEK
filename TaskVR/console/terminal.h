#ifndef _AERO_TERMINAL_H_
#define _AERO_TERMINAL_H_

#include <stdint.h>

typedef void (*PAuxFunc)(uint32_t value);
typedef char (*PAuxInput)(char chr);

/* unprintable chars for magic header number */
#define CMD_MAGIC_HEADER 0x01020304

struct con_cmd_struct{
    uint32_t magic;         /* should always be CMD_MAGIC_HEADER for valid command */
    uint8_t command[16];    /* command name for typing thru terminal */
    uint8_t help[48];       /* short command description */
    void(*callback)(void);  /* callback function to call when command <command> entered */
};

typedef struct con_cmd_struct   cmd_tab_t;

#define cmd_section __attribute__ ((used,section ("CMD")))

#define CON_CMD(name, cb, info)            \
const cmd_tab_t cmd_##name cmd_section = { \
    .magic   = CMD_MAGIC_HEADER,           \
    .command = #name,                      \
    .help    = info,                       \
    .callback = cb,                        \
}

void terminal_print(const char * str);

void terminal_clear(void);
void terminal_goto(uint32_t x, uint32_t y);
void terminal_clear_curline(void);

void terminal_take_input(PAuxInput pFunc);

void terminal_run_aux_task(PAuxFunc pFunc);
void terminal_stop_aux_task(void);

#endif /* #ifndef _AERO_TERMINAL_H_ */
