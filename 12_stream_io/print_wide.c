// cesun, 7/21/20 11:37 AM.

#include <stdio.h>
#include <wchar.h>

const char *stream_orient(FILE *fp) {
    int mode = fwide(fp, 0);
    if (mode < 0) {
        return "narrow";
    } else if (mode > 0) {
        return "wide";
    }
    return "unset";
}


int main() {
    puts(stream_orient(stdout));
    unsigned int arr[] = {0xe6adb8e4,0xb5e68796,0x95afe88b,0x00}; // utf-8
    puts("中文测试");
    puts((const char *) arr);
    puts(stream_orient(stdout));
}

