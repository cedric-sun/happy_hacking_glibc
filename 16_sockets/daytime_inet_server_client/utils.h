// cesun, 10/16/20 8:47 PM.

#ifndef DAYTIME_INET_SERVER_CLIENT_UTILS_H
#define DAYTIME_INET_SERVER_CLIENT_UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

static inline struct sockaddr_in *
init_inet_tcp_addr(struct sockaddr_in *const name,
                   const uint32_t ip, const uint16_t port) {
    name->sin_family = AF_INET;
    name->sin_port = htons(port);
    name->sin_addr.s_addr = htonl(ip);
    return name;
}


static inline int new_inet_tcp_sock(const uint32_t ip, const uint16_t port) {
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

static inline int new_inet_tcp_sock_addrless() {
    int insock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (insock_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return insock_fd;
}

#define HANDSHAKE_FROM_SERVER "i'm server, nice to see you."
#define STRLEN_HANDSHAKE_FROM_SERVER strlen(HANDSHAKE_FROM_SERVER)

#define HANDSHAKE_FROM_CLIENT "i'm client, nice to see you."
#define STRLEN_HANDSHAKE_FROM_CLIENT strlen(HANDSHAKE_FROM_CLIENT)

#define SERVER_LISTEN_PORT 10086

#endif //DAYTIME_INET_SERVER_CLIENT_UTILS_H
