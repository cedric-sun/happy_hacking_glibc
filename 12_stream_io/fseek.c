// cesun, 7/20/20 12:19 AM.

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *demo_txt = fopen("./ro_data.txt","r");
    if (demo_txt == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
//    fseek(demo_txt,3,?); TODO
    fclose(demo_txt);
}