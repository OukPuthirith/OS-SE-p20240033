/* zombie_wait.c — Parent calls wait(), so zombie is cleaned up */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        /* Child — exits immediately */
        printf("Child (PID %d): I'm done. Exiting now.\n", getpid());
        exit(0);
    }

    /* Parent — sleeps 10 seconds BEFORE calling wait() */
    printf("Parent (PID %d): Child PID is %d.\n", getpid(), pid);
    printf("Parent: Sleeping 10 seconds... CHECK FOR ZOMBIE NOW with 'ps aux | grep Z'\n");
    sleep(10);

    /* Now parent calls wait() — zombie disappears */
    wait(NULL);
    printf("Parent: Called wait(). Zombie is now cleaned up.\n");
    printf("Parent: Sleeping 5 more seconds... verify zombie is gone.\n");
    sleep(5);

    return 0;
}
