// cesun, 5/25/20 6:18 PM.

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h> // struct sockaddr_un

int make_named_unsock(const char *name) {
    // PF_LOCAL, PF_UNIX, PF_FILE are equivalent
    int my_unsock_fd = socket(PF_LOCAL, SOCK_DGRAM, 0);
    if (my_unsock_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // bind address
    struct sockaddr_un my_unsock_addr;
    // 110 = short int sum_family (2) + char sun_path[108]
    printf("sizeof(struct sockaddr_un) = %lu\n",sizeof(struct sockaddr_un));
    my_unsock_addr.sun_family = AF_LOCAL;

    // need to call this macro to determine the length argument passing to bind
    size_t my_unsock_len = SUN_LEN(&my_unsock_addr);
    // This is due to the fact that unix domain socket name is a filesystem path
    // that has uncertain length.
    // This is not a problem for inet/inet6 socket, since their address is always
    // represented by fixed length structs.



    return my_unsock_fd;
}

int main() {
}

