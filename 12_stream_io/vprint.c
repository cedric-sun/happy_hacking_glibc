// cesun, 7/21/20 5:01 PM.

#include <stdio.h>
#include <stdarg.h>

#define my_macro_printf(templ, a, b, c, rest...)\
    printf(templ,##rest)

void my_real_printf(const char *templ, ...) {
    va_list args;
    va_start(args, templ);
    for (int i = 0; i < 3; ++i) {
        va_arg(args, int);
    }
    vprintf(templ, args);
    va_end(args);
}


int main() {
    my_macro_printf("%d %d %d\n", 1, 2, 3, 4, 5, 6, 7);
    my_real_printf("%d %d %d\n", 1, 2, 3, 4, 5, 6, 7);
    return 0;
}

