// cesun, 5/26/20 4:16 PM.

#include <stdio.h>
#include <netinet/in.h>

const char *mem_order_hexstr(const unsigned char *start, const int nbyte, char *const buf, const int bufsz) {
    for (int i = 0; i < nbyte && 5 * (i + 1) + 1 <= bufsz; ++i) {
        sprintf(buf + 5 * i, "0x%2x ", *(start + i));
    }
    return buf;
}


int main() {
    uint16_t little_end16 = 0x1234;
#define N 256
    char buf[N];
    puts(mem_order_hexstr(&little_end16, sizeof(little_end16), buf, N));

    uint16_t big_end16 = htons(little_end16); // host to network short
    puts(mem_order_hexstr(&big_end16, sizeof(little_end16), buf, N));

    little_end16 = ntohs(big_end16); // network to host short
    puts(mem_order_hexstr(&little_end16, sizeof(little_end16), buf, N));

    uint32_t little_end32 = 0x1234abcd;
    puts(mem_order_hexstr(&little_end32, sizeof(little_end32), buf, N));

    uint32_t big_end32 = htonl(little_end32); // host to network long (32)
    puts(mem_order_hexstr(&big_end32, sizeof(little_end32), buf, N));

    little_end32 = ntohl(big_end32); // network to host long (32)
    puts(mem_order_hexstr(&little_end32, sizeof(little_end32), buf, N));
}