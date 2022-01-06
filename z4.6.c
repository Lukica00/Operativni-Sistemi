#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int pid0, pid1=0, pid2;
int c = 0;
int q = 0;
void fja(int sigid)
{
    signal(SIGUSR2, fja);
    q++;
    if (q % 2 == 0)
        c = 1;
    if (c)
    {
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
        c = 0;
    }
}
void fja1(int sigid)
{
    signal(SIGUSR1, fja1);
}
void fja2(int sigid)
{
    signal(SIGUSR1, fja2);
}
int main()
{
    srand(time(NULL));
    pid0 = getpid();
    pid1 = fork();
    printf("PID1  %d\n", pid1);
    if (pid1 == 0)
    {
        fprintf(stderr,"KOJ\n");
        signal(SIGUSR1, fja1);
        printf("Pauza 0\n");
        fflush(stdout);
        while (1)
        {
            printf("Pauza 1\n");
            fflush(stdout);
            pause();
            printf("Pauza 2\n");
            fflush(stdout);
            FILE *f = fopen("z4.6a.txt", "w");
            for (int i = 0; i < 1000; i++) // 100 hiljada miliona iteracija
                fprintf(f, "%d", rand() % 10);
            fclose(f);
            kill(pid0, SIGUSR2);
            printf("Poslao 1\n");
            fflush(stdout);
        }
    }
    else
    {
        pid2 = fork();
        printf("PID2  %d\n", pid2);
        if (pid2 == 0)
        {
            signal(SIGUSR1, fja2);
            while (1)
            {
                pause();
                FILE *f = fopen("z4.6b.txt", "w");
                for (int i = 0; i < 1000; i++) // 100 hiljada miliona iteracija
                    fprintf(f, "%c", rand() % 25 + 97);
                fclose(f);
                kill(pid0, SIGUSR2);
                printf("Poslao 2\n");
            }
        }
        else
        {
            for (int i = 0; i < 5; i++)
            {
                fprintf(stderr,"KOJ1\n");
                signal(SIGUSR2, fja);
                kill(pid1, SIGUSR1);
                kill(pid2, SIGUSR1);
                sleep(5); // 10 vaziii
            }
            kill(pid1, SIGTERM);
            kill(pid2, SIGTERM);
        }
    }
}