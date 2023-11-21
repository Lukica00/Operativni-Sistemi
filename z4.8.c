#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#define BR 1234
int s = 0;
int pid,shm;
void handler1(int sig)
{
    signal(SIGUSR2, handler1);
    int *pok = (int *)shmat(shm, NULL, 0);
    for (int j = 0; j < 1024; j++)
    {
        int a = rand() % 10;
        pok[j] = a;
    }
    shmdt(pok);
    kill(getppid(), SIGUSR1);
}
void handler2(int sig)
{
    signal(SIGUSR1, handler2);
    int *pok = (int *)shmat(shm, NULL, SHM_RDONLY);
    for (int j = 0; j < 1024; j++)
    {
        printf("%d ", pok[j]);
    }
    shmdt(pok);
    s++;
    printf("\n LINIJA%d \n\n", s);
    if (s == 4092)
    {
        kill(pid, SIGTERM);
    }
    else
    {
        kill(pid, SIGUSR2);
    }
}
int main()
{
    srand(time(NULL));
    shm = shmget(BR, 1024 * sizeof(int), IPC_CREAT | 0666);
    if ((pid = fork()) == 0)
    {
        handler1(0);
        while (1)
            pause();
    }
    else
    {
        signal(SIGUSR1, handler2);
        wait(NULL);
    }
    shmctl(shm, 0, IPC_RMID);
}