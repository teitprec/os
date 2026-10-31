#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room, spoon[5];

void *phil(void *arg)
{
    int i = (int)(long)arg;

    sem_wait(&room);
    printf("Philosopher %d enters\n", i + 1);

    sem_wait(&spoon[i]);
    sem_wait(&spoon[(i + 1) % 5]);

    printf("Philosopher %d is eating\n", i + 1);
    sleep(2);

    sem_post(&spoon[i]);
    sem_post(&spoon[(i + 1) % 5]);

    printf("Philosopher %d has finished eating\n\n", i + 1);
    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t philosopher[5];

    sem_init(&room, 0, 4);

    for (int i = 0; i < 5; i++)
        sem_init(&spoon[i], 0, 1);

    for (int i = 0; i < 5; i++)
        pthread_create(&philosopher[i], NULL, phil, (void *)(long)i);

    for (int i = 0; i < 5; i++)
        pthread_join(philosopher[i], NULL);

    return 0;
}
