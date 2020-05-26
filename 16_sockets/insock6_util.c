// cesun, 5/25/20 8:51 PM.

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

int main() {
    printf("sizeof(struct sockaddr_in6) "
           "= sizeof(sin6_family)(%lu) + sizeof(sin6_port)(%lu) \n\t"
           "+ sizeof(sin6_flowinfo)(%lu) + sizeof(sin6_addr)(%lu) "
           "+ sizeof(sin6_scope_id)(%lu) = %lu\n",
           MEMBER_SIZE(struct sockaddr_in6, sin6_family),
           MEMBER_SIZE(struct sockaddr_in6, sin6_port),
           MEMBER_SIZE(struct sockaddr_in6, sin6_flowinfo),
           MEMBER_SIZE(struct sockaddr_in6, sin6_addr),
           MEMBER_SIZE(struct sockaddr_in6, sin6_scope_id),
           sizeof(struct sockaddr_in6));
    in6addr_loopback =;
    IN6ADDR_ANY_INIT
    IN6ADDR_LOOPBACK_INIT

}