// cesun, 7/20/20 4:52 PM.

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("sizeof(FILE) = %lu\n", sizeof(FILE));
    FILE *normal_txt = fopen("ro_data.txt","r");
    if (normal_txt == NULL) {
        perror("fopen(\"ro_data.txt\")");
        exit(EXIT_FAILURE);
    }
    printf("%-24s%d", "int _flags", normal_txt->_flags);
    fclose(normal_txt);
}