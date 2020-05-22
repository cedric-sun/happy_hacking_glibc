// cesun, 5/22/20 2:59 PM.


// FILE defined in stdio.h
#include <stdio.h>

int main() {
    // For historical reasons, the type of the C data structure
    // that represents a stream is called FILE rather than “stream”.

    FILE *stream = fopen("/dev/null", "r");
    fclose(stream);
}

