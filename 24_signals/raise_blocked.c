// cesun, 7/19/20 6:43 PM.

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/**
 * Demonstrate that raise() will return immediately if the signal raised is blocked.
 */
volatile sig_atomic_t counter = 0;

void sigterm_handler(int signum) {
    if (counter == 0) {
        raise(signum);
        puts("raise returned!");
    }
    printf("%d\n", counter);
    counter++;
}

int main() {
    struct sigaction term_action = {
            .sa_handler = sigterm_handler,
            .sa_flags=SA_RESTART
    };
    sigemptyset(&term_action.sa_mask);
    sigaction(SIGTERM, &term_action, NULL);
    sleep(1000);
    return 0;
}