// cesun, 5/22/20 8:06 PM.

#include <stdio.h>
#include <stdlib.h>

int main() {
#define CMMD "ls -1"
    FILE *stream = popen(CMMD, "r");
    if (!stream) {
        perror("popen " CMMD);
        return EXIT_FAILURE;
    }
    char *text = NULL;
    size_t n = 0;
    getdelim(&text, &n, -1, stream);
    fputs(text, stdout);
    free(text);
    if (pclose(stream) == -1) { // -1 for errors; 0 to 255 for succ (exit code of command)
        perror("pclose " CMMD);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
#undef CMMD
}