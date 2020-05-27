// cesun, 5/27/20 12:03 PM.

#ifndef HAPPY_HACKING_GLIBC_UTILS_H
#define HAPPY_HACKING_GLIBC_UTILS_H

#include <netinet/in.h>

#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

const char *str_inaddr(const struct in_addr *addr);

const char *str_in6addr(struct in6_addr *addr);

const char *mem_order_hexstr(const void *const start, const int nbyte);

const char *cat_ptr_list(const void *const *const ptr_list, const char *(*xxx2str)(const void *xxx, int *const len), const char *delim);

struct hostent *hostent_deepcopy(struct hostent *hostent_ptr);

void hostent_free(struct hostent *hostent_ptr);

const char *str2str(const void *str, int *const len);

#endif //HAPPY_HACKING_GLIBC_UTILS_H
