// cesun, 5/22/20 3:02 PM.

#include <stdio.h>
#include <stdlib.h>
//#include <errno.h>

void head(FILE *stream, const int n) {
    for (int i = 0; i < n; ++i) {
        int c = fgetc(stream);
        printf("0x%02x ", c);
    }
    putchar('\n');
}

void read_only() {
    // "r" for read only
#define RO_DATA_TXT "./ro_data.txt"
    FILE *ro_data_txt_stream = fopen(RO_DATA_TXT, "r");
    if (!ro_data_txt_stream) { // error = ENOENT if no such file exists
        perror(RO_DATA_TXT);
        exit(EXIT_FAILURE);
    }
    head(ro_data_txt_stream, 5);
    // attempt to write will set errno = EBADF
    int flag = fputs("hello world\n", ro_data_txt_stream);
    if (flag == EOF) {
        perror("write to " RO_DATA_TXT);
    }
    fclose(ro_data_txt_stream);
#undef RO_DATA_TXT
}

void write_only() {
    // "w" for write only
    // `filename` exists: truncate to 0
    // Otherwise new file created
#define WO_DATA_TXT "./wo_data.txt"
    FILE *wo_data_txt_stream = fopen(WO_DATA_TXT, "w");
    fputs("hello world\n", wo_data_txt_stream);
    // attempt to read will set errno = EBADF
    const int c = fgetc(wo_data_txt_stream);
    if (c == EOF) {
        perror("read from " WO_DATA_TXT);
    }
    fclose(wo_data_txt_stream);
#undef WO_DATA_TXT
}

void append_only() {
    // "a" for writing at the end of file only
    // file already exists: initial contents unchanged & output is appended to the end
    // Otherwise, a new, empty file is created
#define AP_DATA_TXT "./ap_data.txt"
    FILE *ap_data_txt_stream = fopen(AP_DATA_TXT, "a");
    if (!ap_data_txt_stream) {
        perror(AP_DATA_TXT);
        exit(EXIT_FAILURE);
    }
    fputs("Barrier \"Boundary of Life and Death\"\n", ap_data_txt_stream);
    fputs("Barrier \"Charming Quadruple Barrier\"\n", ap_data_txt_stream);
    // attempt to read will set errno = EBADF
    const int c = fgetc(ap_data_txt_stream);
    if (c == EOF) {
        perror("read from " AP_DATA_TXT);
    }
    fclose(ap_data_txt_stream);
#undef AP_DATA_TXT
}

void read_write_keep_init() { //TODO
    // "r+" for both read and write. The file must exist.
    // - initial contents of the file are unchanged
    // - the initial file position is at the beginning of the file.
#define NO_SUCH_FILE_TXT "./no_such_file.txt"
    FILE *rw_keep_stream = fopen(NO_SUCH_FILE_TXT, "r+");
    if (!rw_keep_stream) { // error = ENOENT if no such file exists
        perror("r+ open " NO_SUCH_FILE_TXT);
    }
#define RW_KEEP_TXT "./rw_keep.txt"
    rw_keep_stream = fopen(RW_KEEP_TXT, "r+");

#undef NO_SUCH_FILE_TXT
}

void read_write_truncate_init() {
    // "w+" for both read and write
    // If the file already exists, it is truncated to zero length
    // Otherwise, a new file is created.
    //TODO
}

void ignored_b() { //TODO
    // 'b' is ignored on all POSIX conforming systems, including Linux.
    FILE *urand_stream = fopen("/dev/urandom", "rb+"); // equiv to "r+"
    fclose(urand_stream);
}

void cancellation_disabled() {
    FILE *urand_stream = fopen("/dev/urandom", "c");
    fclose(urand_stream);
}

int main() {
    /** standard **/
//    read_only();
//    write_only();
//    append_only();
    read_write_keep_init();
//    ignored_b();

    /** glibc specific **/
//    cancellation_disabled();
}


