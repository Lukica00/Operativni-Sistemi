#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
pthread_mutex_t mutex;
pthread_cond_t uslov1, uslov2;
int *niz;
pthread_t nit[5];

void *Nit(void *arg)
{
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&uslov1, &mutex);
    niz[rand() % 10] += rand() % 21 - 10;
    sleep(1);
    pthread_cond_signal(&uslov2);
    pthread_mutex_unlock(&mutex);
}

void *Stampa(void *arg)
{
    for (int j = 0; j < 4; j++)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&uslov1);
        pthread_cond_wait(&uslov2, &mutex);
        int s = 0;
        for (int i = 0; i < 10; i++)
        {
            s += niz[i];
        }
        if (s % 2 == 0)
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", niz[i]);
            fflush(stdout);
        }
            printf("\n");
        pthread_mutex_unlock(&mutex);
    }
}
int main()
{
    srand(time(NULL));
    niz = calloc(10, sizeof(int));
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&nit[i], NULL, Nit, NULL);
    }
    pthread_create(&nit[4], NULL, Stampa, NULL);
    sleep(1);
    for (int i = 0; i < 5; i++)
    {
        pthread_join(nit[i], NULL);
    }
}