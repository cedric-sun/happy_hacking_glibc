// cesun, 5/26/20 8:30 PM.

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

const char *cat_str_list(const char *const *const str_list, const char *delim) {
    static char buf[10240];
    int tail = 0;
    const int delim_len = strlen(delim);
    for (const char *const *cur = str_list; *cur; cur++) {
        if (cur != str_list) {
            strcpy(buf + tail, delim);
            tail += delim_len;
        }
        strcpy(buf + tail, *cur);
        tail += strlen(*cur);
    }
    buf[tail] = '\0';
    return buf;
}

void dump_service_db() {
    struct servent *serv;
    int lino = 1;
    while (serv = getservent(), serv) {
        printf("%d) s_name: <%s> s_aliases: <%s> %s:%d\n", lino++, serv->s_name,
               cat_str_list(serv->s_aliases, " | "), serv->s_proto, serv->s_port);
    }
}

int main() {
    printf("Port numbers less than IPPORT_RESERVED = %d are reserved for superuser use.\n", IPPORT_RESERVED);
    printf("Port numbers greater than or equal to IPPORT_USERRESERVED = %d are reserved for explicit \n"
           "\tuse; they will never be allocated automatically.\n", IPPORT_USERRESERVED);
    dump_service_db();
}