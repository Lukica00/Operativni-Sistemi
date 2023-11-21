#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    int pip1[2];
    int pip2[2];
    if (pipe(pip1) < 0)
        return -1;
    if (pipe(pip2) < 0)
        return -1;
    if (fork() == 0)
    {
        close(pip1[0]);
        close(pip2[0]);
        char niz[20];
        int s = 0;
        for (int i = 0; i < 20; i++)
        {
            niz[i] = rand() % 75 + 48;
            s += niz[i];
        }
        printf("%d\n", s);
        if (s % 2 == 0)
        {
            int a = 0;
            int b = 1;
            write(pip1[1], &niz[0], sizeof(char));
            write(pip2[1], 0, sizeof(char));
            for (int i = 1; i < 20; i++)
            {
                write(pip1[1], &niz[i], sizeof(char));
            }
        }
        else
        {
            int a = 0;
            int b = 1;
            write(pip2[1], &niz[0], sizeof(char));
            write(pip1[1], 0, sizeof(char));
            for (int i = 1; i < 20; i++)
            {
                write(pip2[1], &niz[i], sizeof(char));
            }
        }
        close(pip1[1]);
        close(pip2[1]);
    }
    else
    {
        close(pip1[1]);
        close(pip2[1]);
        if (fork() == 0)
        {
            close(pip2[0]);
            int s = 0;
            char niz[20];
            read(pip1[0], &niz[0], sizeof(char));
            if (niz[0] != 0)
            {
                FILE *f = fopen("Karakteri.txt", "w");
                read(pip1[0], &niz[0], sizeof(char));
                fprintf(f, "%d ", niz[0]);
                for (int i = 1; i < 20; i++)
                {
                    read(pip1[0], &niz[i], sizeof(char));
                    fprintf(f, "%d ", niz[i]);
                    fflush(f);
                }
                fclose(f);
            }
            close(pip1[0]);
        }
        else if (fork() == 0)
        {
            close(pip1[0]);
            int s = 0;
            char niz[20];
            read(pip2[0], &niz[0], sizeof(char));
            if (niz[0] != 0)
            {
                printf("%d \n", niz[0]);
                fflush(stdout);
                for (int i = 1; i < 20; i++)
                {
                    read(pip2[0], &niz[i], sizeof(char));
                    printf("%d \n", niz[i]);
                    fflush(stdout);
                }
            }
            close(pip2[0]);
        }
    }
}