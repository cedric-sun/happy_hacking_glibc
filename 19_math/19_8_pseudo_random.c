// cesun, 5/23/20 10:02 AM.

#include <stdlib.h>
#include <stdio.h>

#define STR(x) #x
#define STR_FORMAT(x) #x " = " STR(x)

int main() {
    srand(38919);

    puts(STR_FORMAT(RAND_MAX));
    int r0 = rand(); // [0,RAND_MAX]
}