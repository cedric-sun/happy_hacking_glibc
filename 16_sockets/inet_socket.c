// cesun, 5/25/20 7:29 PM.

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in

#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

int main() {
//    int my_sock_fd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in my_sock_addr;
    printf("sizeof(struct sockaddr_in) "
           "= sizeof(sin_family)(%lu) + sizeof(sin_port)(%lu) "
           "+ sizeof(sin_addr)(%lu) + sizeof(paddings)(%lu) = %lu\n",
           MEMBER_SIZE(struct sockaddr_in, sin_family),
           MEMBER_SIZE(struct sockaddr_in, sin_port),
           MEMBER_SIZE(struct sockaddr_in, sin_addr),
           MEMBER_SIZE(struct sockaddr_in, sin_zero),
           sizeof(struct sockaddr_in));

}