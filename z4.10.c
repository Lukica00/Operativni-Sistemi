#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#define BR 1234
int shm, i = 0;
void dete(int sig)
{
    signal(SIGUSR1, dete);
    char *pok = (char *)shmat(shm, NULL, SHM_RDONLY);
    char *linija = malloc(80 * sizeof(char));
    strcpy(linija, pok);
    printf("%s", linija);
    shmdt(pok);
}
int main()
{

    shm = shmget(BR, 80 * sizeof(char), IPC_CREAT | 0666);
    int pid = fork();
    if (pid == 0)
    {
        signal(SIGUSR1, dete);
        while (1)
            pause();
    }
    else
    {
        while (1)
        {
            char *pok = (char *)shmat(shm, NULL, 0);
            char *linija = malloc(80 * sizeof(char));
            int a = 80;
            getline(&linija, (size_t *)&a, stdin);
            strcpy(pok, linija);
            shmdt(pok);
            if (!strcmp(linija, "KRAJ\n"))
            {
                kill(pid, SIGINT);
                break;
            }
            kill(pid, SIGUSR1);
        }
    }
    shmctl(shm, 0, IPC_RMID);
}