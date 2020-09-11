// cesun, 7/21/20 10:45 AM.

#include <stdio.h>
#include <stdio_ext.h>

#define MSG "hello world\n"

void fwrite_demo() {
    fwrite_unlocked(MSG, sizeof(MSG), sizeof(char), stdout);
}

void manual_lock(FILE *fp) {
    flockfile(fp);
    for (int i = 0; i < 100; ++i) {
        if (i % 10 == 0)
            putc_unlocked('\n', fp);
        putc_unlocked((i % 10) + '0', fp);
    }
    funlockfile(fp);
}



int main() {
    fwrite_demo();
    manual_lock(stdout);
    __fsetlocking(stdout, FSETLOCKING_BYCALLER);
    return 0;
}

