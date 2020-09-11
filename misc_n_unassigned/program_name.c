// cesun, 7/21/20 5:42 PM.

#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>

int main() {
    printf("program_invocation_name: %s\n", program_invocation_name);
    printf("program_invocation_short_name: %s\n", program_invocation_short_name);
    return 0;
}