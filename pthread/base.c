// cesun, 7/16/20 1:26 AM.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *foo(void *args) {
    printf("%s\n", (const char *) args);
    return (void *) 0xdeadbeef;
}

int main() {
    pthread_t my_thread;

    const char *str = "hello world";
    int err = pthread_create(&my_thread, NULL, foo, str);
    if (err) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    puts("main thread: waiting for foo...");
    void *ret;
    pthread_join(my_thread, &ret);
    printf("returned pointer: %p\n", ret);
    return 0;
}