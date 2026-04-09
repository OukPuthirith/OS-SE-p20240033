/* three_children.c — Parent creates 3 children, waits for all */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];
    int sleep_times[3] = {15, 20, 25};
    int i;

    printf("Parent (PID %d): Creating 3 child processes...\n", getpid());

    for (i = 0; i < 3; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork");
            exit(1);
        }

        if (pids[i] == 0) {
            /* Child process */
            printf("Child %d (PID %d): Started. Sleeping %d seconds...\n",
                   i + 1, getpid(), sleep_times[i]);
            sleep(sleep_times[i]);
            printf("Child %d (PID %d): Done.\n", i + 1, getpid());
            exit(0);
        }
    }

    /* Parent prints all child PIDs */
    printf("Parent: Child 1 PID=%d, Child 2 PID=%d, Child 3 PID=%d\n",
           pids[0], pids[1], pids[2]);
    printf("Parent: Now waiting for all children...\n");
    printf("Parent: Run 'ps --forest -u $USER' in another terminal NOW!\n");

    /* Wait for all 3 children */
    for (i = 0; i < 3; i++) {
        wait(NULL);
        printf("Parent: One child finished.\n");
    }

    printf("Parent: All children done. Exiting.\n");
    return 0;
}
