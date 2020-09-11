// cesun, 7/18/20 5:28 PM.

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char *buf = NULL;

void sigint_cleanup(int signum) {
    puts("SIGINT cleaning up...");
    free(buf);
    sigaction(SIGINT, &(struct sigaction) {.sa_handler=SIG_DFL}, NULL);
    raise(signum);
}

int main() {
    printf("pid: %d\n", getpid());
    struct sigaction int_action = {
            .sa_handler = sigint_cleanup,
            .sa_flags = SA_RESTART
    };
    sigemptyset(&int_action.sa_mask);
    sigaction(SIGINT, &int_action, NULL);

    buf = malloc(1 << 20); // 1 MiB
    puts("buf allocated");

    sleep(1000);
    return 0;
}