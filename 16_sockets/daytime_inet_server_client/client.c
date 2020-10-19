// cesun, 10/16/20 6:48 PM.
#include "utils.h"
#include <unistd.h>

int main() {
    int local_socket_fd = new_inet_tcp_sock_addrless();
    struct sockaddr_in remote_addr;
    init_inet_tcp_addr(&remote_addr, INADDR_LOOPBACK, SERVER_LISTEN_PORT);

    int connect_flag = connect(local_socket_fd, (struct sockaddr *) &remote_addr,
                               sizeof(remote_addr));
    if (connect_flag == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    } else {
        puts("INFO: Connected to server. Sending handshake...");
    }
    // client first sends handshake
    ssize_t n_sent = send(local_socket_fd, HANDSHAKE_FROM_CLIENT,
                          STRLEN_HANDSHAKE_FROM_CLIENT, 0);
    if (n_sent != STRLEN_HANDSHAKE_FROM_CLIENT) {
        puts("PANIC: n_sent != STRLEN_HANDSHAKE_FROM_CLIENT");
        exit(EXIT_FAILURE);
    } else {
        puts("INFO: Handshake sent.");
    }
    // client then waits for server to perform handshake
    static char buf[256];
    ssize_t n_received = recv(local_socket_fd, buf,
                              STRLEN_HANDSHAKE_FROM_SERVER, MSG_WAITALL);
    if (n_received != STRLEN_HANDSHAKE_FROM_SERVER) {
        puts("PANIC: n_received != STRLEN_HANDSHAKE_FROM_SERVER");
        exit(EXIT_FAILURE);
    } else {
        puts("INFO: Server handshake received.");
    }
    if (strcmp(buf, HANDSHAKE_FROM_SERVER) != 0) {
        puts("PANIC: Server sends bad handshake.");
        exit(EXIT_FAILURE);
    } else {
        puts("INFO: Server handshake validated.");
    }
    // client finally waits for server to send daytime
    int n_char;
    n_received = recv(local_socket_fd, &n_char, sizeof(n_char), MSG_WAITALL);
    n_char = ntohl(n_char);
    if (n_received != (ssize_t) sizeof(n_char)) {
        puts("PANIC: n_received != sizeof(n_char)");
        exit(EXIT_FAILURE);
    } else {
        printf("INFO: daytime meta received = %d\n", n_char);
    }
    n_received = recv(local_socket_fd, buf, n_char, MSG_WAITALL);
    if (n_received != (ssize_t) n_char) {
        puts("PANIC: n_received != (ssize_t) n_char");
        exit(EXIT_FAILURE);
    }
    buf[n_received] = '\0';
    puts(buf);
    close(local_socket_fd);
    return 0;
}
