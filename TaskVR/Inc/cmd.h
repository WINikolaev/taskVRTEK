#ifndef CMD_H_
#define CMD_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "microrl.h"
#include "usart.h"
#include "config.h"

struct con_cmd_struct{
    uint32_t magic;         /* should always be CMD_MAGIC_HEADER for valid command */
    uint8_t command[16];    /* command name for typing thru terminal */
    uint8_t help[48];       /* short command description */
    void(*callback)(void);  /* callback function to call when command <command> entered */
};


typedef struct con_cmd_struct   cmd_tab_t;

void print(const char *str);
int execute (int argc, const char * const * argv);
char ** complete(int argc, const char * const * argv);

#ifdef __cplusplus
}
#endif

#endif /* CMD_H_ */
