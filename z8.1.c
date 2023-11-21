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
#include <sys/shm.h>
#define BR 1234

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int s1, s2;
    int shm;
    struct sembuf sem_lock = {0, -1, 0};
    struct sembuf sem_unlock = {0, 1, 0};
    s1 = semget((__key_t)100, 1, 0666 | IPC_CREAT);
    s2 = semget((__key_t)200, 1, 0666 | IPC_CREAT);
    semctl(s1, 0, SETVAL, 1);
    semctl(s2, 0, SETVAL, 0);

    shm = shmget(BR, 5 * sizeof(int), IPC_CREAT | 0666);

    if (fork() == 0)
    {
        int *pok = (int *)shmat(shm, NULL, SHM_RDONLY);
        for (int i = 0; i < 30; i++)
        {
            semop(s2, &sem_lock, 1);
            int a = pok[i % 5];
            printf("P:%d",a);
            semop(s1, &sem_unlock, 1);
        }
        shmdt(pok);
    }
    else
    {

        int *pok = (int *)shmat(shm, NULL, SHM_RDONLY);
        for (int i = 0; i < 30; i++)
        {
            semop(s1, &sem_lock, 1);
            int a = rand() % 10;
            pok[i % 5] = a;
            printf("V:%d",a);
            semop(s2, &sem_unlock, 1);
        }
        shmdt(pok);

        semctl(s1, 0, IPC_RMID, 0);
        semctl(s2, 0, IPC_RMID, 0);
        shmctl(shm, 0, IPC_RMID);
    }
}