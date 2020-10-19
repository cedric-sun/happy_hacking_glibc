#include "utils.h"
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

struct thread_arg {
    int socket_fd;
    int request_id;
};

void *tcp_handler(void *thread_arg_ptr) {
    struct thread_arg *arg = thread_arg_ptr;
    printf("incoming request #%d, waiting handshake...\n", arg->request_id);
    // server first gets handshake from client
    char handshake_buf[256];
    ssize_t n_received = recv(arg->socket_fd, handshake_buf,
                              STRLEN_HANDSHAKE_FROM_CLIENT, MSG_WAITALL);
    if (n_received != STRLEN_HANDSHAKE_FROM_CLIENT) {
        puts("PANIC:n_received != STRLEN_HANDSHAKE_FROM_CLIENT");
        goto cleanup;
    } else {
        printf("INFO: client #%d handshake validated.\n", arg->request_id);
    }
    // server then send handshake to client
    ssize_t n_send = send(arg->socket_fd, HANDSHAKE_FROM_SERVER, STRLEN_HANDSHAKE_FROM_SERVER, 0);
    if (n_send != STRLEN_HANDSHAKE_FROM_SERVER) {
        puts("PANIC: n_send != STRLEN_HANDSHAKE_FROM_SERVER");
        exit(EXIT_FAILURE);
    } else {
        printf("INFO: client #%d server handshake sent.", arg->request_id);
    }
    time_t now = time(NULL);
    char *now_str = ctime(&now); // string returned by ctime always end with \n
    int n_char = (int) strlen(now_str) - 1; // do not send that \n
    int n_char_netend = htonl(n_char);
    ssize_t n_sent = send(arg->socket_fd, &n_char_netend,
                          sizeof(n_char_netend), 0); // send size first
    if (n_sent != sizeof(n_char)) {
        puts("PANIC: n_sent != sizeof(n_char)");
        goto cleanup;
    } else {
        printf("INFO: client #%d daytime meta sent.\n", arg->request_id);
    }
    n_sent = send(arg->socket_fd, now_str, n_char, 0);
    if (n_sent != n_char) {
        puts("PANIC: n_sent != n_char");
        goto cleanup;
    } else {
        printf("INFO: client #%d daytime body sent.\n", arg->request_id);
    }

    int request_id; // defined behavior for control flow after goto to access variable
                    // declared before goto label
cleanup:
    request_id = arg->request_id;
    close(arg->socket_fd);
    free(arg);
    printf("INFO: client #%d resources are released.\n", request_id);
    return NULL;
}

int main() {
    int server_socket_fd = new_inet_tcp_sock(INADDR_ANY, SERVER_LISTEN_PORT);
    int listen_flg = listen(server_socket_fd, 16);
    if (listen_flg == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; ++i) {
        struct sockaddr_in client_addr;
        socklen_t ignored;
        int accept_fd = accept(server_socket_fd, (struct sockaddr *) &client_addr, &ignored);
        if (accept_fd == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        // essentially a thread pool is ideal here, but for the sake of simplicity...
        pthread_t detaching_thread_id;
        struct thread_arg *arg = malloc(sizeof(*arg));
        arg->socket_fd = accept_fd;
        arg->request_id = i;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&detaching_thread_id, &attr, tcp_handler, arg);
    }
    puts("Wait 3 seconds for last connection before shutting down ...");
    sleep(3);
}
