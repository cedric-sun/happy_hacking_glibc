// cesun, 5/25/20 5:28 PM.

#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <string.h>

int main() {
    // glibc manual documented that IFNAMSIZ is a constant of type size_t,
    // but on my machine its a macro that expands to literal 16
    printf("Buffer of IFNAMSIZ = %lu bytes is sufficient to hold any ifname.\n", IFNAMSIZ);
    struct if_nameindex *ifs = if_nameindex();
    if (ifs == NULL) {
        // error
    }

    // if_index is unsigned int
    for (struct if_nameindex *cur = ifs; cur->if_index; cur++) {
        printf("%d: %s\n", cur->if_index, cur->if_name);

        // conversion between if_name and if_index
        char buf[IF_NAMESIZE];
        if (strcmp(cur->if_name, if_indextoname(cur->if_index, buf))) {
            puts("wtf");
        }
        if (cur->if_index != if_nametoindex(cur->if_name)) {
            puts("wtf");
        }
    }
    if_freenameindex(ifs); // must be freed
}