#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t semP, semN;

int *niz;
void *Nit1(void *arg)
{
    int N = *(int *)arg;
    for (int i = 1; i < N; i+=2)
    {
        sem_wait(&semN);
        niz[i] += 2;
        sem_post(&semP);
    }
}
void *Nit2(void *arg)
{
    int N = *(int *)arg;
    for (int i = 0; i < N - 1; i += 2)
    {
        sem_wait(&semP);
        for (int j = i + 2; j < N; j += 2)
        {
            if (niz[i] < niz[j])
            {
                int pom = niz[i];
                niz[i] = niz[j];
                niz[j] = pom;
            }
        }
        sem_post(&semN);
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    niz = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &niz[i]);
    }
    pthread_t nit1, nit2;
    sem_init(&semP, 0, 0);
    sem_init(&semN, 0, 1);
    pthread_create(&nit1, NULL, Nit1, (void *)&N);
    pthread_create(&nit2, NULL, Nit2, (void *)&N);
    pthread_join(nit1, NULL);
    pthread_join(nit2, NULL);
    for (int i = 0; i < N; i++)
    {
        printf("%d", niz[i]);
    }
    sem_destroy(&semP);
    sem_destroy(&semN);
}