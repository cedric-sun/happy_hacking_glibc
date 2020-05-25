// cesun, 5/22/20 1:36 PM.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void read_from_pipe(int fd) {
    FILE *stream = fdopen(fd, "r");
    int c;
    while ((c = fgetc(stream)) != EOF) {
        putchar(c);
    }
    fclose(stream);
}

void write_to_pipe(int fd) {
    FILE *stream = fdopen(fd, "w");
    fputs("hello world.\n", stream);
    fputs("Connection Closed.\n", stream);
    fclose(stream);
}

int main() {
    int fds[2];
    if (pipe(fds)) { // 0 for succ, -1 for failure
        perror("Error on creating pipe");
        exit(EXIT_FAILURE);
    }
    // required usage: read from fds[0] ; write to fds[1]
    pid_t child_pid = fork();
    if (child_pid == 0) {
        close(fds[1]); // in child, close sending fd
        read_from_pipe(fds[0]);
        return EXIT_SUCCESS;
    } else if (child_pid == -1) { // -1 if fork failed
        perror("fork failed");
        return EXIT_FAILURE;
    } else {
        close(fds[0]); // in parent, close receiving fd
        write_to_pipe(fds[1]);
        return EXIT_SUCCESS;
    }
}