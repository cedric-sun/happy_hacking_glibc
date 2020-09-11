// cesun, 7/17/20 4:52 PM.

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "../unsung_utils/utils.h"

void sigusr_handler(int signum) {
    if (signum == SIGUSR1) {
        puts("SIGUSR1 arrived.");
    } else if (signum == SIGUSR2) {
        puts("SIGUSR2 arrived.");
    }
}

int main() {
    printf("pid: %d\n", getpid());

    struct sigaction newact;
    newact.sa_handler = sigusr_handler;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0; // SA_RESTART is not set

    int sa_flag = sigaction(SIGUSR1, &newact, NULL);
    if (sa_flag == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    sa_flag = sigaction(SIGUSR2, &newact, NULL);
    if (sa_flag == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // SIGUSR1 and SIGUSR2 will no longer terminate the process now.

    for (int i = 0; i < 10000; ++i) {
        heavy_work_spin();
        if (i % 10 == 0) {
            printf("%d\n", i);
        }
    }
    return 0;
}