#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *worker(void *arg)
{
    int id = *(int *)arg;

    printf("Worker %d started\n", id);

    sleep(5);

    printf("Worker %d finished\n", id);

    return NULL;
}

int main()
{
    pthread_t threads[4];
    int ids[4];

    for(int i=0;i<4;i++)
    {
        ids[i]=i+1;
        pthread_create(&threads[i],NULL,worker,&ids[i]);
    }

    for(int i=0;i<4;i++)
        pthread_join(threads[i],NULL);

    printf("All workers joined.\n");

    return 0;
}
