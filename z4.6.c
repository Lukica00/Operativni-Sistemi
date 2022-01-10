#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int pid0, pid1 = 0, pid2;
int q = 0, i = 0, j = 0;
void roditelj(int sig)
{
    signal(SIGUSR2, roditelj);
    if (q == 1)
    {
        q = 0;
        FILE *f = fopen("z4.6a.txt", "r");
        char in;
        while (fscanf(f, "%c", &in) == 1)
        {
            int ni = in - 48;
            printf("%d", ni);
        }
        fflush(stdout);
        fclose(f);
        f = fopen("z4.6b.txt", "r");
        while (fscanf(f, "%c", &in) == 1)
        {
            printf("%c", in);
        }
        printf("\n");
        fclose(f);
        i++;
        printf("\n%d\n", i);
        if (i == 20)
        {
            kill(pid1, SIGINT);
            kill(pid2, SIGINT);
            exit(0);
        }
    }
    else
    {
        q++;
    }
}
void dete1(int sig)
{
    signal(SIGUSR1, dete1);
    FILE *f = fopen("z4.6a.txt", "w");
    for (int i = 0; i < 1000; i++)
        fprintf(f, "%d", rand() % 10);
    fclose(f);

    kill(pid0, SIGUSR2);
}
void dete2(int sig)
{
    signal(SIGUSR1, dete2);
    FILE *f = fopen("z4.6b.txt", "w");
    for (int i = 0; i < 1000; i++)
        fprintf(f, "%c", rand() % 25 + 97);
    fclose(f);
    kill(pid0, SIGUSR2);
}

void alarmantno(int sig)
{
    signal(SIGUSR2, roditelj);
    kill(pid1, SIGUSR1);
    kill(pid2, SIGUSR1);
    signal(SIGALRM, alarmantno);
    alarm(2);
    j++;
    printf("j:%d\n", j);
}
int main()
{
    srand(time(NULL));
    pid0 = getpid();
    pid1 = fork();
    if (pid1 == 0)
    {
        signal(SIGUSR1, dete1);
        while (1)
        {
            pause();
        }
    }
    else
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            signal(SIGUSR1, dete2);
            while (1)
            {
                pause();
            }
        }
        else
        {
            signal(SIGALRM, alarmantno);
            alarm(2);
            while (1)
            {
                pause();
            }
        }
    }
}