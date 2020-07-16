// cesun, 5/25/20 3:54 PM.

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../unsung_utils/utils.h"

int inet_tcp_sock(const uint32_t ip, const uint16_t port) {
    int insock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (insock_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sock_name;
    init_inet_tcp_addr(&sock_name, INADDR_ANY, port);


    int bind_err = bind(insock_fd, (struct sockaddr *) &sock_name, sizeof(sock_name));
    if (bind_err) { // 0 for succ; -1 for error
        perror("bind");
        exit(EXIT_FAILURE);
    }
    return insock_fd;
}

int main() {
    int insock_fd = inet_tcp_sock(INADDR_ANY, 14455);
    struct sockaddr_in remote_addr;
    init_inet_tcp_addr(&remote_addr, INADDR_LOOPBACK, 8080);

    int connect_flag = connect(insock_fd, &remote_addr, sizeof(remote_addr));
    if (connect_flag == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    const char buf[] = "hello world\n";
    write(insock_fd, buf, sizeof(buf)); // sending \0 too

    printf("closing connection...");
    int close_flag = close(insock_fd);
    if (close_flag) {
        perror("fd close");
        exit(EXIT_FAILURE);
    }
    return 0;
}