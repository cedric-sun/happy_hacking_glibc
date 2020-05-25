// cesun, 5/25/20 1:06 PM.


//TODO

#include <stdio.h>
#include <limits.h>

#define STR(x) #x
#define STR_FORMAT(x) #x " = " STR(x)

int main() {
    puts("pipe buffer size: "STR_FORMAT(PIPE_BUF));
}
