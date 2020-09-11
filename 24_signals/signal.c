// cesun, 7/17/20 4:01 PM.

#define _GNU_SOURCE

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void sigusr_handler(int signum) {
    if (signum == SIGUSR1) {
        puts("SIGUSR1 arrived");
    } else {
        puts("SIGUSR2 arrived");
    }
}

int main() {
    printf("pid: %d\n", getpid());
    // return previously effective handler, or SIG_ERR on error.
    sighandler_t handler = signal(SIGUSR1, sigusr_handler);
    if (handler == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    handler = signal(SIGUSR2, sigusr_handler);
    if (handler == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    // the DEFINED semantics of sleep() is to return upon
    // the arrival of any signal that is not ignored.
    sleep(1000);
    return 0;
}
