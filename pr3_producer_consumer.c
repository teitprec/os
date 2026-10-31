#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

int buffer, count, pdelay, cdelay;
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    for (int i = 0; i < count; i++) {
        int item = rand() % 100 + 1;

        sleep(pdelay);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer = item;
        printf("Producer produced %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < count; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        printf("Consumer consumed %d\n", buffer);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(cdelay);
    }
    return NULL;
}

int main()
{
    pthread_t p, c;

    printf("Enter number of items: ");
    scanf("%d", &count);
    printf("Enter producer delay: ");
    scanf("%d", &pdelay);
    printf("Enter consumer delay: ");
    scanf("%d", &cdelay);
    srand(time(NULL));

    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
