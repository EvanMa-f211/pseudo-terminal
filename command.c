#include "pseudo_terminal.h"

void cat(char** command_list){
    
    if(command_list[0][0] == '-'){

    }else{ // no option (default)

    }

}

void mk(char** command_list, int command_list_num){
    // wrong usage
    if(command_list_num != 1){
        printf("command error\n");
        printf("usage: mkdir [directory name]\n");
        return;
    }

    char* directory = command_list[0];

    // duplicated name
    if (access(directory, F_OK) >= 0){
        printf("%s: duplicated name\n", directory);
        return;
    }

    if (mkdir(directory, S_IRUSR | S_IWUSR | S_IXUSR) < 0)
        system_error("mkdir failed");

}

void rm(char** command_list, int command_list_num){
    // wrong usage
    if(command_list_num != 1){
        printf("command error\n");
        printf("usage: rm [file name]\n");
        return;
    }
    
    char* file = command_list[0];
    struct stat file_stat;

    // file doesn't exist
    if (access(file, F_OK) < 0){
        printf("%s doesn't exist\n", file);
        return;
    }

    // check status of the file/directory
    if (lstat(file, &file_stat) < 0)
        system_error("lstat failed");
    
    // is regular file or directory
    if (S_ISREG(file_stat.st_mode) || S_ISDIR(file_stat.st_mode)){
        // file uid == process uid
        if(file_stat.st_uid == getuid()){
            if (remove(file) < 0){
                if(errno == EBUSY)
                    printf("%s cannot be removed because it is being used\n", file);
                else if(errno == EEXIST || errno == ENOTEMPTY)
                    printf("%s is not empty, or there are hard links to %s\n", file, file);
                else
                    system_error("remove failed\n");
            }
        }else{
            printf("%s: permission denied\n", file);
            return;
        }
    }
    // neither regular file nor directory
    else{
        printf("%s is not a regular file or a directory\n", file);
    }
    
}

