// cesun, 7/15/20 6:36 PM.

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include "../unsung_utils/utils.h"
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

volatile sig_atomic_t server_shutdown = 0;

void sigterm_handler(int signum) {
    server_shutdown = 1;
}

void *do_request(void *args) {

}

int main() {
    struct sigaction sigterm_action = {
            .sa_handler = sigterm_handler,
            .sa_flags = SA_RESTART
    };
    sigemptyset(&sigterm_action.sa_mask);
    sigaction(SIGTERM, &sigterm_action, NULL);

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

    volatile int counter = 0;

    for (int i = 0; !server_shutdown; ++i) {
        printf("serving request #%d\n", i);
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
        pthread_t req_thread;
        pthread_create(&req_thread, NULL, do_request, );
        char buf[256];
        int n = snprintf(buf, sizeof(buf), "hello from server, you are the %d-th served connection.\n", i);
        write(accept_fd, buf, n);
        close(accept_fd);
    }
    puts("shutting down...");

    close(serversock_fd);
}