// cesun, 7/21/20 4:47 PM.

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf;
    asprintf(&buf, "hello, %s", "world");
    puts(buf);
    free(buf);
    return 0;
}

