#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#define MEM_KEY 1234
#define SEM_KEY 4321
int main()
{
    srand(time(NULL));
    int i, j;
    int semid;
    struct sembuf sem_lock = {0, -1, 0};
    struct sembuf sem_unlock = {0, 1, 0};
    semid = semget((key_t)SEM_KEY, 1, 0666 | IPC_CREAT);
    semctl(semid, 0, SETVAL, 0);
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    if (fork() != 0)
    {
        int shm_id = shmget(MEM_KEY, m * n * sizeof(int), IPC_CREAT | 0666);
        int *shm_ptr = shmat(shm_id, NULL, 0);
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                shm_ptr[i * n + j] = rand() % 100;
                printf("%d ",shm_ptr[i * n + j]);
            }
            printf("\n");
        }
        semop(semid, &sem_unlock, 1);
        shmdt(shm_ptr);
        wait(NULL);
        shmctl(shm_id, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID, NULL);
    }
    else
    {
        int shm_id = shmget(MEM_KEY, m * n * sizeof(int), IPC_CREAT | 0666);
        int *shm_ptr = shmat(shm_id, NULL, 0);
        semop(semid, &sem_lock, 1);
        for (i = 0; i < m; i++)
        {
            int maxel = 0;
            for (j = 0; j < n; j++)
            {
                if (shm_ptr[i * n + j] > maxel)
                    maxel = shm_ptr[i * n + j];
            }
            printf("Maksimalni element vrste %d je: %d\n", i, maxel);
        }
        shmdt(shm_ptr);
    }
}