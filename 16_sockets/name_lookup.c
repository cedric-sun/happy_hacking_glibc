// cesun, 5/26/20 2:22 PM.

/* man 3 gethostname:
 *
 * The gethostbyname*(), gethostbyaddr*(), herror(), and hstrerror()
 * functions are obsolete.  Applications should use getaddrinfo(3),
 * getnameinfo(3), and gai_strerror(3) instead.
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>

#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

// mask based inspection
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

// not include the terminating NULL
int ptr_list_len(char **ptr_list) {
    char **cur;
    for (cur = ptr_list; *cur; cur++);
    return cur - ptr_list;
}

struct hostent *hostent_deepcopy(struct hostent *hostent_ptr) {
    struct hostent *new_hostent = malloc(sizeof(*new_hostent));
    new_hostent->h_addrtype = hostent_ptr->h_addrtype;
    const int addr_len = new_hostent->h_length = hostent_ptr->h_length;
    new_hostent->h_name = strcpy(malloc(strlen(hostent_ptr->h_name) + 1), hostent_ptr->h_name);
    int h_aliases_len = ptr_list_len(hostent_ptr->h_aliases);
    new_hostent->h_aliases = malloc(sizeof(char *) * (h_aliases_len + 1));
    for (int i = 0; i < h_aliases_len; ++i) {
        new_hostent->h_aliases[i] = strcpy(malloc(strlen(hostent_ptr->h_aliases[i]) + 1),
                                           hostent_ptr->h_aliases[i]);
    }
    new_hostent->h_aliases[h_aliases_len] = NULL;
    int h_addr_list_len = ptr_list_len(hostent_ptr->h_addr_list);
    new_hostent->h_addr_list = malloc(sizeof(char *) * (h_addr_list_len + 1));
    for (int i = 0; i < h_addr_list_len; ++i) {
        new_hostent->h_addr_list[i] = memcpy(malloc(addr_len), hostent_ptr->h_addr_list[i], addr_len);
    }
    new_hostent->h_addr_list[h_addr_list_len] = NULL;
    return new_hostent;
}

void hostent_free(struct hostent *hostent_ptr) {
    free(hostent_ptr->h_name);
    for (char **cur = hostent_ptr->h_aliases; *cur; cur++) {
        free(*cur);
    }
    free(hostent_ptr->h_aliases);
    for (char **cur = hostent_ptr->h_addr_list; *cur; cur++) {
        free(*cur);
    }
    free(hostent_ptr->h_addr_list);
    free(hostent_ptr);
}

void hostent_info(struct hostent *demo_hostent) {
    printf("h_name: %s\n", demo_hostent->h_name);
    fputs("h_aliases: ", stdout);
    for (char **cur = demo_hostent->h_aliases; *cur; cur++) {
        printf("%s\t", *cur);
    }
    putchar('\n');
    printf("h_addrtype: %s\t\th_length: %d\n",
           demo_hostent->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6", demo_hostent->h_length);
    fputs("h_addr_list: ", stdout);
    for (char **cur = demo_hostent->h_addr_list; *cur; cur++) {
        if (demo_hostent->h_addrtype == AF_INET)
            printf("%s\t", str_inaddr((struct in_addr *) *cur));
        else if (demo_hostent->h_addrtype == AF_INET6)
            printf("%s\t", str_in6addr((struct in6_addr *) *cur));
        else
            fputs("Unknown AF.", stderr);
    }
    putchar('\n');
}

void gethostbyname_demo(const char *hostname) {
    struct hostent *tmp = gethostbyname(hostname);
    if (tmp == NULL) {
        herror("gethostbyname");
    } else {
        /* man 3 gethostbyname:
         *
         * The functions gethostbyname() and gethostbyaddr() may return pointers to static data,
         * which may be overwritten by later calls. Copying the struct hostent does not suffice,
         * since it contains pointers; a deep copy is required. */
//        memcpy(&demo_hostent, tmp, sizeof(struct hostent)); // not enough!
        struct hostent *demo_hostent = hostent_deepcopy(tmp);
        hostent_info(demo_hostent);
        hostent_free(demo_hostent);
    }
}

// GNU extension
void gethostbyname2_demo(const char *hostname, int af) {
    struct hostent *tmp = gethostbyname2(hostname, af);
    if (tmp == NULL) {
        herror("gethostbyname");
    } else {
        struct hostent *demo_hostent = hostent_deepcopy();
        hostent_info(demo_hostent);
        hostent_free(demo_hostent);
    }
}

void gethostbyaddr_demo() {
    //TODO
}

int main() {
    printf("sizeof(struct hostent) = sizeof(char *h_name)(%lu) "
           "+ sizeof(char **h_aliases)(%lu) + sizeof(int h_addrtype)(%lu) \n\t"
           "+ sizeof(int h_length)(%lu) + sizeof(char **h_addr_list)(%lu) = %lu\n",
           MEMBER_SIZE(struct hostent, h_name),
           MEMBER_SIZE(struct hostent, h_aliases),
           MEMBER_SIZE(struct hostent, h_addrtype),
           MEMBER_SIZE(struct hostent, h_length),
           MEMBER_SIZE(struct hostent, h_addr_list),
           sizeof(struct hostent));

    gethostbyname_demo("cesun.io");
    puts("---------------");
    gethostbyname_demo("v2ex.com");
    puts("---------------");
    gethostbyname_demo("google.com");
    puts("---------------");
//    gethostbyname2_demo("google.com", AF_INET6);
};
