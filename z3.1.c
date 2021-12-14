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
        int niz[20];
        int s = 0;
        for (int i = 0; i < 20; i++)
        {
            niz[i] = rand() % 100;
            s += niz[i];
        }
        printf("%d\n", s);
        if (s % 2 == 0)
        {
            int a = 0;
            int b = 1;
            write(pip1[1], &b, sizeof(int));
            write(pip2[1], &a, sizeof(int));
            for (int i = 0; i < 20; i++)
            {
                write(pip1[1], &niz[i], 20 * sizeof(int));
            }
        }
        else
        {
            int a = 0;
            int b = 1;
            write(pip2[1], &b, sizeof(int));
            write(pip1[1], &a, sizeof(int));
            for (int i = 0; i < 20; i++)
            {
                write(pip2[1], &niz[i], 20 * sizeof(int));
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
            int niz[20];
            int tmp;
            read(pip2[0], &tmp,sizeof(int));
            if (tmp != 0)
            {                
                FILE *f = fopen("Brojevi.txt", "w");
                for (int i = 0; i < 20; i++)
                {
                    read(pip1[0],&niz[i],sizeof(int));
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
            int niz[20];
            int tmp;
            read(pip2[0], &tmp, sizeof(int));
            if (tmp != 0)
            {
                for (int i = 0; i < 20; i++)
                {
                    read(pip2[0],&niz[i],sizeof(int));
                    printf("%d \n", niz[i]);
                    fflush(stdout);
                }
            }
            close(pip2[0]);
        }
    }
}