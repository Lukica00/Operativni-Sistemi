#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int arg, char *argv[])
{
    sem_t *s1;
    s1 = sem_open("/sema1", O_CREAT, 0666, 1);
    sem_t *s2;
    s2 = sem_open("/sema2", O_CREAT, 0666, 0);
    
    FILE *f;
    char ime[20] = "fajl.txt";
    //int N = *argv[2] - 48;
    int N = 3;

    //strcpy(ime, "./");
    //strcat(ime, argv[1]);

    f = fopen(ime, "w");
    int n = fork();
    if (n == 0)
    {
        for (int i = 0; i < N; i++)
        {
            sem_wait(s1);
            fprintf(f, "%d ", rand() % 20);
            fprintf(f, "%d ", rand() % 20);
            fprintf(f, "%d //", rand() % 20);
            fflush(f);
            sem_post(s2);
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            sem_wait(s2);
            fprintf(f, "%d ", (rand() % 20) * (-1));
            fprintf(f, "%d\n", (rand() % 20) * (-1));
            fflush(f);
            sem_post(s1);
        }
    }
    sem_close(s1);
    sem_close(s2);
    sem_unlink("/sema1");
    sem_unlink("/sema2");
    fclose(f);
    return 0;
}