// cesun, 5/26/20 4:16 PM.

#include <stdio.h>
#include <netinet/in.h>

const char *mem_order_hexstr(const void *const start, const int nbyte) {
    static char buf[2048];
    for (int i = 0; i < nbyte; ++i) {
        sprintf(buf + 5 * i, "0x%02x ", *((unsigned char *) start + i));
    }
    return buf;
}


int main() {
    uint16_t little_end16 = 0x1234;

    puts(mem_order_hexstr(&little_end16, sizeof(little_end16)));

    uint16_t big_end16 = htons(little_end16); // host to network short
    puts(mem_order_hexstr(&big_end16, sizeof(little_end16)));

    little_end16 = ntohs(big_end16); // network to host short
    puts(mem_order_hexstr(&little_end16, sizeof(little_end16)));

    uint32_t little_end32 = 0x1234abcd;
    puts(mem_order_hexstr(&little_end32, sizeof(little_end32)));

    uint32_t big_end32 = htonl(little_end32); // host to network long (32)
    puts(mem_order_hexstr(&big_end32, sizeof(little_end32)));

    little_end32 = ntohl(big_end32); // network to host long (32)
    puts(mem_order_hexstr(&little_end32, sizeof(little_end32)));
}