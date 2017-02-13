// http://blog.csdn.net/morewindows/article/details/7442333

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int g=0;
sem_t metux;

void *thread(void *vargp){
    pthread_detach(pthread_self());
    struct timespec t = {0, 50000000};
    nanosleep(&t, NULL);
    sem_wait(&metux);
    g++;
    printf("thread %d, global:%d\n", *((int *)vargp), g);
    sem_post(&metux);
    free(vargp);
    return NULL;
}

int main(){
    sem_init(&metux, 0, 1);
    pthread_t tid;
    int i, *j;
    for ( i=0; i<10; i++ ) {
        j = (int *)malloc(sizeof(int));
        *j = i;
        pthread_create(&tid, NULL, thread, j);
    }
    sleep(1); // wait until all peer threads end
    return 0;
}
