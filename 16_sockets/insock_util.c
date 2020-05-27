// cesun, 5/25/20 7:29 PM.

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h>

#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

const char *str_inaddr(const struct in_addr *addr) {
    // `in_addr_t s_addr` in in_addr is stored in big endianness
    /*
     *                              <- low                     high ->
     * 127.0.0.1 high_end               127     0       0       1       = 0x0100007f
     * mask0                            0xff    0       0       0       = 0x000000ff
     * mask1                            0       0xff    0       0       = 0x0000ff00
     * mask1                            0       0       0xff    0       = 0x00ff0000
     * mask1                            0       0       0       0xff    = 0xff000000
     */
    uint32_t x = addr->s_addr;
    static char buf[256];
    sprintf(buf, "%d.%d.%d.%d", x & 0xffU, (x >> 8) & 0xffU, (x >> 16) & 0xffU, x >> 24);
    return buf;
}


// byte iteration based inspection
const char *str_in6addr(struct in6_addr *addr) {
    static char buf[256];
    // addr->__in6_u is a 16 bytes union and should be interpreted as a 128-bit big endian integer
    // s6_addr[16] is a macro array for 8-bit access
    // s6_addr16[8] for 16-bit access; s6_addr32[4] for 32-bit access
    sprintf(buf, "%4x", ntohs(addr->s6_addr16[0]));
    int tail = 4;
    for (int i = 1; i < 8; ++i) {
        sprintf(buf + tail, ":%04x", ntohs(addr->s6_addr16[i]));
        tail += 5;
    }
    buf[tail] = '\0';
    return buf;
}

void inet_pton_ntop_demo(const char *addr_str) {
#define ADDR_STR_BUFSZ 256
    char buf[ADDR_STR_BUFSZ];
    struct in_addr parsed_inaddr;
    int pton_flag = inet_pton(AF_INET, addr_str, &parsed_inaddr);
    if (pton_flag == -1) { // -1 if the first argument is not valid address family
        perror("inet_pton"); // EAFNOSUPPORT
        return;
    } else if (pton_flag == 0) { // 0 if the 2nd argument cannot be parsed
        // errno is NOT set
        fprintf(stderr, "%s is not valid AF_INET address\n", addr_str);
        return;
    } else { // 1 for succ
        puts(str_inaddr(&parsed_inaddr));
    }
    const char *converted_addr_str = inet_ntop(AF_INET, &parsed_inaddr, buf, ADDR_STR_BUFSZ);
    // NULL on failure, buf on succ
    if (!converted_addr_str) {
        perror("inet_ntop");
    } else {
        puts(addr_str);
    }
#undef ADDR_STR_BUFSZ
}

void inet6_pton_ntop_demo(const char *addr_str) {
#define ADDR_STR_BUFSZ 256
    char buf[ADDR_STR_BUFSZ];
    struct in6_addr parsed_in6addr;
    int pton_flag = inet_pton(AF_INET6, addr_str, &parsed_in6addr);
    if (pton_flag == -1) { // -1 if the first argument is not valid address family
        perror("inet_pton"); // EAFNOSUPPORT
        return;
    } else if (pton_flag == 0) { // 0 if the 2nd argument cannot be parsed
        // errno is NOT set
        fprintf(stderr, "%s is not valid AF_INET6 address\n", addr_str);
        return;
    } else { // 1 for succ
        puts(str_in6addr(&parsed_in6addr));
    }
    const char *converted_addr_str = inet_ntop(AF_INET6, &parsed_in6addr, buf, ADDR_STR_BUFSZ);
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

    // weird enough these macros are defined in host byte order
    // see also:
    // https://stackoverflow.com/questions/6081892/does-sin-addr-s-addr-inaddr-any-need-htonl-at-all
    in_addr_t tmp = htonl(INADDR_LOOPBACK);
    puts(str_inaddr((struct in_addr *) &tmp));

    tmp = htonl(INADDR_ANY);
    puts(str_inaddr((struct in_addr *) &tmp));

    tmp = htonl(INADDR_BROADCAST);
    puts(str_inaddr((struct in_addr *) &tmp));

    tmp = htonl(INADDR_NONE); // used by legacy API to indicate error
    puts(str_inaddr((struct in_addr *) &tmp));

    puts("-----------------------");

    /********* util functions provided by arpa/inet.h *********/

    // inet_aton and inet_ntoa handle only IPv4 address; use inet_pton and inet_ntop instead.

    // inet_addr, inet_network, inet_makeaddr, inet_lnaof, inet_netof are deprecated due to
    // the abolition of classful ip addressing or bad API design.

    inet_pton_ntop_demo("216.58.194.46");
    puts("-----------------------");
    inet6_pton_ntop_demo("2001:4860:4860::8888");
}