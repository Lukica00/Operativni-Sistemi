#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t uslov1,uslov2;

void *Neparni(void *a)
{
    FILE *f = (FILE *)a;
    pthread_mutex_lock(&mutex);
    printf("Aloha1\n");
    for (int i = 1; i <= 200; i += 2)
    {
        pthread_cond_wait(&uslov1,&mutex);
        printf("AlohaCekanije1\n");
        fprintf(f,"%d ",i);
        pthread_cond_signal(&uslov2);
        printf("AlohaCekanije11\n");
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void *Parni(void *a)
{
    FILE *f = (FILE *)a;
    pthread_mutex_lock(&mutex);
    printf("Aloha2\n");
    for (int i = 2; i <= 200; i += 2)
    {
        pthread_cond_wait(&uslov2,&mutex);
        printf("AlohaCekanije2\n");
        fprintf(f,"%d ",i);
        pthread_cond_signal(&uslov1);
        printf("AlohaCekanije22\n");
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    FILE *f = fopen("z1.2.txt", "w");

    pthread_t nit1, nit2;

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&uslov1,NULL);
    pthread_cond_init(&uslov2,NULL);

    pthread_create(&nit1, NULL, Neparni, (void *)f);
    pthread_create(&nit2, NULL, Parni, (void *)f);

    printf("Aloha0\n");
    pthread_cond_signal(&uslov1);
    printf("Aloha00\n");

    pthread_join(nit1, NULL);
    pthread_join(nit2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&uslov1);
    pthread_cond_destroy(&uslov2);
}
