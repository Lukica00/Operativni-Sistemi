#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
pthread_mutex_t mutex;
pthread_cond_t uslov;
int *niz;
pthread_t nit[5];

void *Nit(void *arg)
{
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&uslov, &mutex);
    niz[rand() % 10] += rand() % 21 - 10;
    sleep(3);
    pthread_cond_signal(&uslov);
    pthread_mutex_unlock(&mutex);
}

void *Stampa(void *arg)
{
    for (int i = 0; i < 4; i++)
    {
        pthread_join(nit[i], NULL);
    }
    int s = 0;
    for (int i = 0; i < 10; i++)
    {
        s += niz[i];
    }
    if (s % 2 == 0)
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", niz[i]);
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
    sleep(3);
    pthread_cond_signal(&uslov);
    pthread_create(&nit[5], NULL, Stampa, NULL);
    pthread_join(nit[5], NULL);
}