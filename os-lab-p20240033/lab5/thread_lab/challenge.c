#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

volatile int keep_running = 1;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("\n[SIGINT received] Shutting down threads...\n");
        keep_running = 0;
    }
}

void* worker_func(void* arg) {
    long tid = (long)arg;
    while (keep_running) {
        printf("Thread %ld running (pthread id: %lu)\n", tid, pthread_self());
        sleep(1);
    }
    printf("Thread %ld exiting cleanly.\n", tid);
    pthread_exit(NULL);
}

int main() {
    signal(SIGINT, sig_handler);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker_func, (void*)1L);
    pthread_create(&t2, NULL, worker_func, (void*)2L);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("All threads cleanly exited. Goodbye.\n");
    return 0;
}