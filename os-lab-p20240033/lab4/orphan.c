#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid > 0) {
        printf("Parent (PID %d): I'm exiting now. Child PID is %d.\n", getpid(), pid);
        exit(0);
    }
    printf("Child (PID %d): My parent was PID %d.\n", getpid(), getppid());
    printf("Child: Sleeping 60 seconds... check my PPID with 'ps -o pid,ppid,cmd -p %d'\n", getpid());
    sleep(60);
    printf("Child (PID %d): My parent is now PID %d.\n", getpid(), getppid());
    return 0;
}
