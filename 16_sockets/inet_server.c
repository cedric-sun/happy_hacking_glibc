// cesun, 7/15/20 6:36 PM.

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include "../unsung_utils/utils.h"
#include <unistd.h>

int main() {
    int serversock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (serversock_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_sockaddr;
    init_inet_tcp_addr(&server_sockaddr, INADDR_ANY, 8080);
    int bind_flag = bind(serversock_fd, &server_sockaddr, sizeof(server_sockaddr));
    if (bind_flag == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    int listen_flag = listen(serversock_fd, 16);
    if (listen_flag == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; ++i) {
        puts("waiting in accept()...");
        struct sockaddr_in client_addr;
        socklen_t len;
        int accept_fd = accept(serversock_fd, &client_addr, &len);
        if (accept_fd == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        if (len != sizeof(struct sockaddr_in)) {
            fputs("PANIC", stderr);
            exit(EXIT_FAILURE);
        }
        char buf[256];
        int n = snprintf(buf, sizeof(buf), "hello from server, you are the %d-th served connection.\n", i);
        write(accept_fd, buf, n);
        close(accept_fd);
    }

    close(serversock_fd);
}