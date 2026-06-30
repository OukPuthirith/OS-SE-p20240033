#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void shutdown_handler(int sig) {
    printf("\n[Signal Caught] Intercepted Signal %d. Running cleanup...\n", sig);
    exit(0);
}

int main() {
    signal(SIGINT, shutdown_handler);
    signal(SIGTERM, shutdown_handler);
    printf("[Signal Demo] Registered at PID: %d. Press Ctrl+C to trap...\n", getpid());
    while(1) { sleep(1); }
    return 0;
}
