// http://blog.csdn.net/morewindows/article/details/7577591

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int g=0;
sem_t metux;
sem_t slots;
sem_t items;

void *producer(void *vargp){
    pthread_detach(pthread_self());
    struct timespec t = {0, 50000000};
    nanosleep(&t, NULL);
    sem_wait(&slots);

    sem_wait(&metux);
    // do something here
    g++;
    printf("producer %d, items:%d\n", *((int *)vargp), g);
    sem_post(&metux);

    sem_post(&items);
    free(vargp);
    return NULL;
}

void *consumer(void *vargp){
    pthread_detach(pthread_self());
    struct timespec t = {0, 50000000};
    nanosleep(&t, NULL);
    sem_wait(&items);

    sem_wait(&metux);
    // do something here
    g--;
    printf("consumer %d, items:%d\n", *((int *)vargp), g);
    sem_post(&metux);

    sem_post(&slots);
    free(vargp);
    return NULL;
}

int main(){
    sem_init(&metux, 0, 1);
    sem_init(&slots, 0, 1);
    sem_init(&items, 0, 0);
    pthread_t tid;
    int i, *j, *k;
    for ( i=0; i<10; i++ ) {
        j = (int *)malloc(sizeof(int));
        k = (int *)malloc(sizeof(int));
        *j = *k = i;
        pthread_create(&tid, NULL, producer, j);
        pthread_create(&tid, NULL, consumer, k);
    }
    sleep(1); // wait until all peer threads end
    return 0;
}
