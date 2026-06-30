#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("\nCaught SIGINT!\n");
    printf("Cleaning up...\n");
}

int main()
{
    signal(SIGINT, handler);

    while(1)
    {
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}

