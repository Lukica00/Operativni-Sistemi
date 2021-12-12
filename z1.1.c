#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semP, semN;

void *Neparni(void *a)
{
    FILE *f = (FILE *)a;
    for (int i = 1; i <= 20; i += 2)
    {

        sem_wait(&semN);
        fprintf(f,"%d ",i);
        sem_post(&semP);
    }
    return NULL;
}
void *Parni(void *a)
{
    FILE *f = (FILE *)a;
    for (int i = 2; i <= 20; i += 2)
    {
        sem_wait(&semP);
        fprintf(f,"%d ",i);
        sem_post(&semN);
    }
    return NULL;
}

int main()
{
    FILE *f = fopen("z1.1.txt", "w");

    pthread_t nit1, nit2;
    sem_init(&semP, 0, 0);
    sem_init(&semN, 0, 1);
    pthread_create(&nit1, NULL, Neparni, (void *)f);
    pthread_create(&nit2, NULL, Parni, (void *)f);
    pthread_join(nit1, NULL);
    pthread_join(nit2, NULL);
    sem_destroy(&semP);
    sem_destroy(&semN);
}