#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main(int arg, char *argv[])
{
    int s1, s2;
    union semun
    {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } sem;
    struct sembuf sem_lock = {0, -1, 0};
    struct sembuf sem_unlock = { 0, 1, 0};
    s1 = semget((__key_t)100, 1, 0666 | IPC_CREAT);
    s2 = semget((__key_t)200, 1, 0666 | IPC_CREAT);
    sem.val = 1;
    semctl(s1, 0, SETVAL, sem);
    sem.val = 0;
    semctl(s2, 0, SETVAL, sem);
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
            semop(s1, &sem_lock, 1);
            fprintf(f, "%d ", rand() % 20);
            fprintf(f, "%d ", rand() % 20);
            fprintf(f, "%d //", rand() % 20);
            fflush(f);
            semop(s2, &sem_unlock, 1);
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            semop(s2, &sem_lock, 1);
            fprintf(f, "%d ", (rand() % 20) * (-1));
            fprintf(f, "%d\n", (rand() % 20) * (-1));
            fflush(f);
            semop(s1, &sem_unlock, 1);
        }
    }
    semctl(s1, 0, IPC_RMID, 0);
    semctl(s2, 0, IPC_RMID, 0);
    fclose(f);
    return 0;
}