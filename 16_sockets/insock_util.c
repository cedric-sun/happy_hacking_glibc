// cesun, 5/25/20 7:29 PM.

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h>

#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

void print_inaddr(const struct in_addr *const addr) {
    // mind the big endianness
    uint32_t x = addr->s_addr;
    printf("%d.%d.%d.%d\n", x & 0xff, (x >> 8) & 0xff, (x >> 16) & 0xff, x >> 24);
}

void print_inaddrt_numdot(in_addr_t x) {
    printf("%d.%d.%d.%d\n", x >> 24, (x >> 16) & 0xff, (x >> 8) & 0xff, x & 0xff);
}

void inet_pton_ntop_demo(int af, const char *addr_str) {
#define ADDR_STR_BUFSZ 256
    char buf[ADDR_STR_BUFSZ];
    struct in_addr parsed_inaddr;
    int pton_flag = inet_pton(af, addr_str, &parsed_inaddr);
    if (pton_flag == -1) { // -1 if the first argument is not valid address family
        perror("inet_pton"); // EAFNOSUPPORT
        return;
    } else if (pton_flag == 0) { // 0 if the 2nd argument cannot be parsed
        // errno is NOT set
        fprintf(stderr, "%s is not valid %s address\n", addr_str,
                af == AF_INET ? "AF_INET" : "AF_INET6");
        return;
    } else { // 1 for succ
        if (af == AF_INET)
            print_inaddr(&parsed_inaddr);
    }
    const char *converted_addr_str = inet_ntop(af, &parsed_inaddr, buf, ADDR_STR_BUFSZ);
    // NULL on failure, buf on succ
    if (!converted_addr_str) {
        perror("inet_ntop");
    } else {
        puts(addr_str);
    }
#undef ADDR_STR_BUFSZ
}

int main() {
    struct sockaddr_in my_sock_addr;
    printf("sizeof(struct sockaddr_in) "
           "= sizeof(sin_family)(%lu) + sizeof(sin_port)(%lu) "
           "+ sizeof(sin_addr)(%lu) + sizeof(paddings)(%lu) = %lu\n",
           MEMBER_SIZE(struct sockaddr_in, sin_family),
           MEMBER_SIZE(struct sockaddr_in, sin_port),
           MEMBER_SIZE(struct sockaddr_in, sin_addr),
           MEMBER_SIZE(struct sockaddr_in, sin_zero),
           sizeof(struct sockaddr_in));

    // these macros are defined in host byte order
    print_inaddrt_numdot(INADDR_LOOPBACK);
    print_inaddrt_numdot(INADDR_ANY);
    print_inaddrt_numdot(INADDR_BROADCAST);
    print_inaddrt_numdot(INADDR_NONE); // used by legacy API to indicate error

    puts("-----------------------");

    /********* util functions provided by arpa/inet.h *********/

    // inet_aton and inet_ntoa handle only IPv4 address; use inet_pton and inet_ntop instead.

    // inet_addr, inet_network, inet_makeaddr, inet_lnaof, inet_netof are deprecated due to
    // the abolition of classful ip addressing or bad API design.

    inet_pton_ntop_demo(AF_INET, "216.58.194.46");
    puts("-----------------------");
    inet_pton_ntop_demo(AF_INET6, "2001:4860:4860::8888");
}