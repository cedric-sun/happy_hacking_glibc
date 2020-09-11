// cesun, 7/18/20 5:54 PM.

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "../unsung_utils/utils.h"

volatile sig_atomic_t alarmed = 0; // int

void alarm_handler(int signum) {
    alarmed = 1;
}

int main() {
    dup2(1, 2);
    struct sigaction alarm_action = {
            .sa_handler = alarm_handler,
            .sa_flags = SA_RESTART
    };
    sigemptyset(&alarm_action.sa_mask);
    sigaction(SIGALRM, &alarm_action, NULL);

    alarm(1);

    int i = 0;
    while (!alarmed) {
        heavy_work_spin();
        printf("iteration #%d\n", i);
        i++;
    }

    printf("quiting...");
    return 0;
}

