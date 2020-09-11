#include <stdio.h>
#include <stdlib.h>

void wide_fopen() {
    FILE *wide_stream = fopen("ro_data.txt", "rcss=UTF-8");
}

void decide_by_fisrt_op() {
    FILE *wide_stream = fopen("ro_data.txt", "r");
}

int main() {

}