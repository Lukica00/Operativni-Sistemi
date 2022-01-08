#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
int s = 0;
int pid;
void handler1(int sig)
{
    signal(SIGUSR2, handler1);
    FILE *f = fopen("prenos.dat", "wb");
    for (int j = 0; j < 1024; j++)
    {
        int a = rand() % 10;
        fwrite(&a, 4, 1, f);
    }
    fclose(f);
    kill(getppid(), SIGUSR1);
}
void handler2(int sig)
{
    signal(SIGUSR1, handler2);

    FILE *f = fopen("prenos.dat", "rb");
    for (int j = 0; j < 1024; j++)
    {
        int a;
        fread(&a, 4, 1, f);
        printf("%d ", a);
    }
    fclose(f);
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
}