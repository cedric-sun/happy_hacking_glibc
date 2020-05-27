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
#include "../unsung_utils/utils.h"



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
        struct hostent *demo_hostent = hostent_deepcopy(tmp);
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
