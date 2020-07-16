// cesun, 7/15/20 2:27 PM.

#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// 16.8.3
// A socket pair is much like a pipe;
// the main difference is that the socket pair is bidirectional,
// whereas the pipe has one input-only end and one output-only end
int main() {
    const char CHILD_MSG[] = "hello world from child.";
    const char PARENT_MSG[] = "world hello from parent.";

    int fds[2]; // parent use fds[0], child use fds[1]
    // protocol family must be PF_LOCAL
    if (socketpair(PF_LOCAL, SOCK_STREAM, 0, fds) == -1) {
        perror("socketpair");
        exit(EXIT_FAILURE);
    }
    pid_t child = fork();
    if (child == 0) {
        close(fds[0]);
        printf("CHILD: sending - %s\n", CHILD_MSG);
        write(fds[1], CHILD_MSG, sizeof(CHILD_MSG));
        char child_recv_buf[sizeof(PARENT_MSG)];
        ssize_t nbyte = read(fds[1], child_recv_buf, sizeof(PARENT_MSG));
        printf("CHILD: received - %s\n", child_recv_buf);
        close(fds[1]);
    } else if (child < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else {
        close(fds[1]);
        printf("PARENT: sending - %s\n", PARENT_MSG);
        write(fds[0], PARENT_MSG, sizeof(PARENT_MSG));
        char parent_recv_buf[sizeof(CHILD_MSG)];
        ssize_t nbyte = read(fds[0], parent_recv_buf, sizeof(CHILD_MSG));
        printf("PARENT: received - %s\n", parent_recv_buf);
        close(fds[0]);
        int wstatus;
        if (wait(&wstatus) == -1) { // prevent zombie
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}