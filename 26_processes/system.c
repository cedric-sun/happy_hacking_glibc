// cesun, 5/22/20 8:07 PM.

#include <stdlib.h>
#include <stdio.h>

// system = fork + execl sh -c command + wait (i.e. synchronous)
int main() {
    int sh_avail = system(NULL); //pass in NULL to test shell availability
    if (!sh_avail) {
        fputs("No shell available", stderr);
        exit(EXIT_FAILURE);
    }
    int flag = system("non_existing_command");
    if (flag == -1) { // child process creation error
        perror("");
        exit(EXIT_FAILURE);
    }
    if (flag == 127) { // exec error
        //If a shell could not be executed in the child process, then the  re‐
        //          turn  value  is  as  though  the  child  shell terminated by calling
        //          _exit(2) with the status 127. (?)
        //TODO
    }
    printf("0x%x\n", flag);
}