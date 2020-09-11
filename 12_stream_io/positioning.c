// cesun, 7/21/20 9:09 PM.

#include <stdio.h>

void drain(FILE *txt) {
    int c;
    while ((c = getc_unlocked(txt)) != EOF) {
        printf("%x %ld\n", c, ftell(txt));
    }
    printf("EOF %ld\n", ftell(txt));
}

int main() {
    FILE *txt = fopen("ro_data.txt", "r");
    drain(txt);
    puts("---------------fseek to 30");
    fseek(txt, 30, SEEK_SET);
    drain(txt);
    puts("---------------rewind");
    rewind(txt);
    drain(txt);
    fclose(txt);
}

