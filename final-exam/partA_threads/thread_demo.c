#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

void* worker_function(void* arg) {
    int id = *(int*)arg;
    pid_t lwp_id = syscall(SYS_gettid);
    printf("[Worker %d] Alive. Kernel LWP ID: %d\n", id, lwp_id);
    sleep(6); // Kept alive to capture mapping evidence
    return NULL;
}

int main() {
    int worker_count = 3; // Scenario value matching OrbitWorks
    pthread_t threads[worker_count];
    int thread_ids[worker_count];

    printf("[Main] Base Process PID: %d\n", getpid());
    for (int i = 0; i < worker_count; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker_function, &thread_ids[i]);
    }
    for (int i = 0; i < worker_count; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("[Main] Processing threads complete.\n");
    return 0;
}
