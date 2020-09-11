// cesun, 7/20/20 7:12 PM.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void multi_stage_print() {
    fprintf(stdout, "hi, ");
    fprintf(stdout, "this is ");
    fprintf(stdout, "the output");
    fprintf(stdout, "from thread #");
    fprintf(stdout, "%lu\n", pthread_self());
}

/*
hi, this is the outputfrom thread #139701620430592
hi, this is the outputfrom thread #139701620430592
the outputhi, from thread #this is the outputfrom thread #139701620430592
hi, this is the outputfrom thread #139701620430592
139701628823296
hi, this is the outputfrom thread #139701628823296
hi, this is the outputfrom thread #139701628823296
 */
void *foo(void *args) {
    for (int i = 0; i < 10000; ++i) {
        multi_stage_print();
    }
    return NULL;
}

void *bar(void *args) {
    for (int i = 0; i < 10000; ++i) {
        flockfile(stdout);
        multi_stage_print();
        funlockfile(stdout);
    }
    return NULL;
}

int main() {
    pthread_t t0, t1;
    int err = pthread_create(&t0, NULL, bar, NULL);
    if (err) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    err = pthread_create(&t1, NULL, bar, NULL);
    if (err) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
}