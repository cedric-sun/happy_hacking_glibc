// cesun, 5/22/20 8:06 PM.

#include <stdio.h>
#include <stdlib.h>

void pipe_read_stdout() {
#define CMMD "ls -1"
    FILE *stream = popen(CMMD, "r"); // CMMD process inherits stdin
    if (!stream) { // NULL for failure and errno is set
        perror("popen " CMMD);
        return;
    }
    char *text = NULL;
    size_t n = 0;
    getdelim(&text, &n, -1, stream);
    fputs(text, stdout);
    free(text);
    if (pclose(stream) == -1) { // -1 for errors; 0 to 255 for succ (exit code of command)
        perror("pclose " CMMD);
        return;
    }
#undef CMMD
}

void pipe_write_stdin() {
#define CMMD "grep at --color=always"
    FILE *stream = popen(CMMD, "w"); // CMMD process inherits stdout
    if (!stream) {
        perror("popen " CMMD);
        return;
    }
    fputs("nation-state\n"
          "naturopathy\n"
          "palatinate\n"
          "patinate\n"
          "patriarchate\n", stream);
    if (pclose(stream) == -1) { // -1 for errors; 0 to 255 for succ (exit code of command)
        perror("pclose " CMMD);
        return;
    }
#undef CMMD
}

int main() {
    // mode must be one of: "r" "w" "re" "we"
    pipe_read_stdout();
    puts("------------");
    pipe_write_stdin();
}