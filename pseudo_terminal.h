#ifndef PSEUDO_TERMINAL
#define PSEUDO_TERMINAL

#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_SIZE 2048
#define CMD_LIST_SIZE 64

extern sigjmp_buf terminal_jmp;
extern sigset_t default_sigset;

void system_error(const char* error_str);

void rm(char** command_list, int command_list_num);
void mk(char** command_list, int command_list_num);


#endif