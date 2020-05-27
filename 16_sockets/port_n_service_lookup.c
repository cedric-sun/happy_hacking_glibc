// cesun, 5/26/20 8:30 PM.

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include "../unsung_utils/utils.h"

const char *str2str(const void *str, int *const len) {
    *len = strlen(str);
    return str;
}

void dump_service_db() {
    struct servent *serv;
    int lino = 1;
    while (serv = getservent(), serv) {
        printf("%d) s_name: <%s> s_aliases: <%s> %s:%d\n", lino++, serv->s_name,
               cat_ptr_list(serv->s_aliases, str2str, " | "), serv->s_proto, /*TODO*/ntohl(serv->s_port));
    }
    endservent();
}


int main() {
    printf("Port numbers less than IPPORT_RESERVED = %d are reserved for superuser use.\n", IPPORT_RESERVED);
    printf("Port numbers greater than or equal to IPPORT_USERRESERVED = %d are reserved for explicit \n"
           "\tuse; they will never be allocated automatically.\n", IPPORT_USERRESERVED);
    dump_service_db();
//    struct servent *submissions_serv = getservbyname("submissions", "tcp");
//    if (submissions_serv == NULL) {
//        // oops
//    } else {
//        puts(mem_order_hexstr(&submissions_serv->s_port, sizeof(submissions_serv->s_port)));
//    }
}