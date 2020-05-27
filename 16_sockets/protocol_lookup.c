// cesun, 5/27/20 3:13 PM.

#include <stdio.h>
#include <netdb.h>
#include "../unsung_utils/utils.h"

const char *str_protoent(struct protoent *pentp) {
    static char buf[1024];
    // p_proto is in host byte order
    sprintf(buf, "p_name: <%s> p_aliases: <%s> p_proto: %d", pentp->p_name,
            cat_ptr_list(pentp->p_aliases, str2str, " | "), pentp->p_proto);
    return buf;
}

void dump_protoents() {
    struct protoent *cur;
    while (cur = getprotoent(), cur) {
        puts(str_protoent(cur));
    }
}

int main() {
//    dump_protoents();
    struct protoent *tcp_protoent = getprotobyname("tcp");
    // also need deep copy if saving the result is necessary
    if (tcp_protoent == NULL) {
        // oops
    } else {
        puts(str_protoent(tcp_protoent));
    }

    // getprotobynumber argument is also in host byte order
    struct protoent *ipv6_icmp_protoent = getprotobynumber(58);
    if (ipv6_icmp_protoent == NULL) {
        // oops
    } else {
        puts(str_protoent(ipv6_icmp_protoent));
    }
}