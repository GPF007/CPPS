#include "../utils.h"


//每条命令长度最长为32
static char cmds[COMMAND_NUMBER][32] = {
    "USER",
    "PASS",
    "LIST",
    "RETR",
    "STOR",
};

//处理函数指针
// cmd_handler_t <=> void (*)(char *)
// intterupt_handler_t <=> void (*)(pt_regs *)
typedef void (*cmd_handler_t)(char *, char *);

static char* end_mark = "END_MARK";


cmd_handler_t cmd_handlers[COMMAND_NUMBER];

void init_handlers();

int get_cmd(char* cmd,int write_fd);

void handler_user(char* cmd, char* resp);
void handler_pass(char* cmd, char* resp);
void handler_list(char* cmd, char* resp);
void handler_retr(char* cmd, char* resp);
void handler_stor(char* cmd, char* resp);