// cesun, 5/27/20 12:03 PM.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <netdb.h>

// mask based inspection
const char *str_inaddr(const struct in_addr *addr) {
    // `in_addr_t s_addr` in in_addr is stored in big endianness
    /*
     *                              <- low                     high ->
     * 127.0.0.1 high_end               127     0       0       1       = 0x0100007f
     * mask0                            0xff    0       0       0       = 0x000000ff
     * mask1                            0       0xff    0       0       = 0x0000ff00
     * mask1                            0       0       0xff    0       = 0x00ff0000
     * mask1                            0       0       0       0xff    = 0xff000000
     */
    uint32_t x = addr->s_addr;
    static char buf[256];
    sprintf(buf, "%d.%d.%d.%d", x & 0xffU, (x >> 8) & 0xffU, (x >> 16) & 0xffU, x >> 24);
    return buf;
}

// byte iteration based inspection
const char *str_in6addr(struct in6_addr *addr) {
    static char buf[256];
    // addr->__in6_u is a 16 bytes union and should be interpreted as a 128-bit big endian integer
    // s6_addr[16] is a macro array for 8-bit access
    // s6_addr16[8] for 16-bit access; s6_addr32[4] for 32-bit access
    int tail = 0;
    for (int i = 0; i < 8; ++i) {
        if (i != 0) buf[tail++] = ':';
        sprintf(buf + tail, "%04x", ntohs(addr->s6_addr16[i]));
        tail += 4;
    }
    buf[tail] = '\0';
    return buf;
}

const char *str2str(const void *str, int *const len) {
    *len = strlen(str);
    return str;
}

const char *cat_ptr_list(const void *const *const ptr_list, const char *(*xxx2str)(const void *xxx, int *const len), const char *delim) {
    static char buf[10240];
    int tail = 0;
    const int delim_len = strlen(delim);
    for (const void *const *cur = ptr_list; *cur; cur++) {
        if (cur != ptr_list) {
            memcpy(buf + tail, delim, delim_len);
            tail += delim_len;
        }
        int len;
        const char *str = xxx2str(*cur, &len);
        memcpy(buf + tail, str, len);
        tail += len;
    }
    buf[tail] = '\0';
    return buf;
}

// not include the terminating NULL
int ptr_list_len(const void *const *const ptr_list) {
    const void *const *cur;
    for (cur = ptr_list; *cur; cur++);
    return cur - ptr_list;
}

struct hostent *hostent_deepcopy(struct hostent *hostent_ptr) {
    struct hostent *new_hostent = malloc(sizeof(*new_hostent));
    new_hostent->h_addrtype = hostent_ptr->h_addrtype;
    const int addr_len = new_hostent->h_length = hostent_ptr->h_length;
    new_hostent->h_name = strcpy(malloc(strlen(hostent_ptr->h_name) + 1), hostent_ptr->h_name);
    int h_aliases_len = ptr_list_len(hostent_ptr->h_aliases);
    new_hostent->h_aliases = malloc(sizeof(char *) * (h_aliases_len + 1));
    for (int i = 0; i < h_aliases_len; ++i) {
        new_hostent->h_aliases[i] = strcpy(malloc(strlen(hostent_ptr->h_aliases[i]) + 1),
                                           hostent_ptr->h_aliases[i]);
    }
    new_hostent->h_aliases[h_aliases_len] = NULL;
    int h_addr_list_len = ptr_list_len(hostent_ptr->h_addr_list);
    new_hostent->h_addr_list = malloc(sizeof(char *) * (h_addr_list_len + 1));
    for (int i = 0; i < h_addr_list_len; ++i) {
        new_hostent->h_addr_list[i] = memcpy(malloc(addr_len), hostent_ptr->h_addr_list[i], addr_len);
    }
    new_hostent->h_addr_list[h_addr_list_len] = NULL;
    return new_hostent;
}

void hostent_free(struct hostent *hostent_ptr) {
    free(hostent_ptr->h_name);
    for (char **cur = hostent_ptr->h_aliases; *cur; cur++) {
        free(*cur);
    }
    free(hostent_ptr->h_aliases);
    for (char **cur = hostent_ptr->h_addr_list; *cur; cur++) {
        free(*cur);
    }
    free(hostent_ptr->h_addr_list);
    free(hostent_ptr);
}

const char *mem_order_hexstr(const void *const start, const int nbyte) {
    static char buf[2048];
    for (int i = 0; i < nbyte; ++i) {
        sprintf(buf + 5 * i, "0x%02x ", *((unsigned char *) start + i));
    }
    return buf;
}