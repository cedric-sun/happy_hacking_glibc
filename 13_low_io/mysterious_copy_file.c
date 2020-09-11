// cesun, 7/24/20 5:22 PM.

#define _GNU_SOURCE

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int inc_bin_fd = open("inc.bin", O_RDONLY);
    if (inc_bin_fd < 0) {
        perror("open ro inc.bin");
        exit(EXIT_FAILURE);
    }
    int inc_bin_bkup_fd = open("inc.bin.backup", O_WRONLY | O_CREAT | O_TRUNC);
    if (inc_bin_bkup_fd < 0) {
        perror("open wo creat trunc inc.bin");
        exit(EXIT_FAILURE);
    }
    off64_t i_off = 0, o_off = 0;
    ssize_t n_byte = copy_file_range(inc_bin_fd, &i_off, inc_bin_bkup_fd, &o_off, (1 << 15) - 1, 0);
    if (n_byte == -1) {
        perror("copy_file_range");
        exit(EXIT_FAILURE);
    }
    printf("%ld bytes copied.\n", n_byte);
    close(inc_bin_bkup_fd);
    close(inc_bin_bkup_fd);
}