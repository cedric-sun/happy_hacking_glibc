// cesun, 5/26/20 8:30 PM.

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include "../unsung_utils/utils.h"

const char *str_servent(const struct servent *const servp) {
    static char buf[256];
    sprintf(buf, "s_name: <%s> s_aliases: <%s> %s:%d", servp->s_name,
            cat_ptr_list(servp->s_aliases, str2str, " | "),
            servp->s_proto, ntohs(*(uint16_t *) &servp->s_port));  /* mind the interpretation of s_port */
    return buf;
}

void dump_service_db() {
    struct servent *servp;
    int lino = 1;
    while (servp = getservent(), servp) {
        printf("%d) %s\n", lino++, str_servent(servp));
    }
//    endservent();
}


int main() {
    printf("Port numbers less than IPPORT_RESERVED = %d are reserved for superuser use.\n", IPPORT_RESERVED);
    printf("Port numbers greater than or equal to IPPORT_USERRESERVED = %d are reserved for explicit \n"
           "\tuse; they will never be allocated automatically.\n", IPPORT_USERRESERVED);

//    dump_service_db();

    struct servent *submissions_servp = getservbyname("submissions", "tcp");
    if (submissions_servp == NULL) {
        // oops
    } else {
        puts(str_servent(submissions_servp));
    }

    // port argument needs to be big endian
    struct servent *http_alt_servp = getservbyport(htons(8080), "tcp");
    if (http_alt_servp == NULL) {
        // oops
    } else {
        puts(str_servent(http_alt_servp));
    }
}