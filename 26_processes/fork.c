// cesun, 5/22/20 1:48 PM.

#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t child_pid = fork(); // parent process sees child PID; child process sees 0
    if (child_pid == 0) {
        puts("Printed by child process.");
    } else {
        printf("Child PID = %d\n", child_pid);
    }
}