// cesun, 5/25/20 12:04 PM.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
#define NP_NAME "tmp_fifo"
    int mkfifo_flag = mkfifo(NP_NAME, S_IRUSR | S_IWUSR);
    if (mkfifo_flag) { // 0 for succ, -1 for error
        perror("cannot make fifo `tmp_fifo`");
        exit(EXIT_FAILURE);
    }
    FILE *stream = NULL;
    int child_pid = fork();
    if (child_pid == -1) {
        // fork failed ...
    } else if (child_pid == 0) {
        stream = fopen(NP_NAME, "r");
        char *buf = NULL;
        size_t n = 0;
        getdelim(&buf, &n, EOF, stream);
        fputs(buf, stdout);
        free(buf);
        // reader remove pipe ; don't remove it twice
        int unlink_flag = unlink(NP_NAME);
        if (unlink_flag) { // 0 for succ, -1 for error
            perror("cannot delete named pipe");
            exit(EXIT_FAILURE);
        }
    } else {
        stream = fopen(NP_NAME, "w");
        fputs("hello world!\n", stream);
    }
    fclose(stream);
#undef NP_NAME
}