// cesun, 7/24/20 3:43 PM.

#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>

#define N 4

int main(void) {
    struct iovec vecs[N];
    for (int i = 0; i < N; ++i) {
        vecs[i].iov_base = malloc(BUFSIZ);
        vecs[i].iov_len = BUFSIZ;
    }

    int fd = open("inc.bin", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    ssize_t n_read = readv(fd, vecs, N);
    close(fd);
    printf("%ld bytes read.\n", n_read);

    int *tmp = vecs[3].iov_base;
    for (int i = 0; i < 16/*2048*/; ++i) {
        printf("%d\t", tmp[i]);
    }

    for (int i = 0; i < N; ++i) {
        free(vecs[i].iov_base);
    }
}

