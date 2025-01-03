#include "pseudo_terminal.h"

const char* const delim = " \n\t";

sigjmp_buf terminal_jmp;
sigset_t default_sigset;
char command[BUF_SIZE];

void system_error(const char* error_str){
    fprintf(stderr, "%s \n", error_str);
    fprintf(stderr, "errno: %d\n", errno);
    exit(1);
}


void handle_command(char* command){

    // prepare for exec
    char* cmd;
    char* command_list[CMD_LIST_SIZE];
    int command_list_num = 0;

    cmd = strtok(command, delim);
    // command nothing
    if(cmd == NULL)
        siglongjmp(terminal_jmp, -1);
    // command "exit"
    if(strcmp(cmd, "exit") == 0)
        exit(0);

    for(int i=0;i<CMD_LIST_SIZE - 1;i++){
        command_list[i] = strtok(NULL, delim);
        // break if we approach the end of the command
        if(command_list[i] == NULL)
            break;
        command_list_num++;
    }
    command_list[CMD_LIST_SIZE-1] = NULL;

    if (strcmp(cmd, "rm") == 0){
        rm(command_list, command_list_num);
    }



    // check if the file is available or not
    /*
    if (access(exec_file, X_OK) < 0){
        if(exec_file != NULL){
            printf("%s: command not found, missing file or permission denied\n", exec_file);
        }
        siglongjmp(terminal_jmp, -1);
    }
    // fork child to exec
    pid_t pid = fork();
    if(pid == 0){
        sigprocmask(SIG_SETMASK, &default_sigset, NULL);
        execv(exec_file, exec_argv);
    }else{
        int statloc;
        waitpid(pid, &statloc, 0);
    }
    */
}

int main(){

    // set stdout and stderr to unbuffered
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char cwd[BUF_SIZE];

    while(1){

        // bloack all the signal
        sigset_t terminal_sigset;
        sigfillset(&terminal_sigset);
        sigdelset(&terminal_sigset, SIGTSTP);
        sigdelset(&terminal_sigset, SIGQUIT);
        if (sigprocmask(SIG_BLOCK, &terminal_sigset, &default_sigset) < 0)
            system_error("sigprocmask: SIG_BLOCK failed");

        sigsetjmp(terminal_jmp, 1);

        if (getcwd(cwd, BUF_SIZE) == NULL)
            system_error("getcwd failed");
        
        if (printf("%s$#$", cwd) < 0)
            system_error("printf failed");
        if (fgets(command, BUF_SIZE, stdin) < 0)
            system_error("scanf failed");

        handle_command(command);

    }


    return 0;
}