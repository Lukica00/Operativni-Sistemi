#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
int p = 0;
void ctrlc(int s)
{
    signal(SIGINT, ctrlc);
    if (p == 0 || p == 1)
    {
        p++;
    }
    else if (p == 3)
    {
        exit(0);
    }
}
void ctrlz(int s)
{
    signal(SIGTSTP, ctrlz);
    if (p == 2)
        p++;
    else
        p = 0;
}
int main()
{
    signal(SIGINT, ctrlc);
    signal(SIGTSTP, ctrlz);
    while (1)
    {
        pause();
    }
}