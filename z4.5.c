#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
    char imeIzv[10];
    char imeOdr[10];
    strcpy(imeIzv, argv[1]);
    strcpy(imeOdr, argv[2]);
    int pip[2];
    pipe(pip);
    if (fork() == 0)
    {
        close(pip[1]);
        char ime[10];
        read(pip[0], &ime, 10 * sizeof(char));
        FILE *f = fopen(ime, "w");
        void *buf = malloc(200);
        while (read(pip[0], buf, 200))
        {
            printf("PRIMIO:%s\n",buf);
            fwrite(buf, 1, 200, f);
        }
    }
    else
    {
        close(pip[0]);
        FILE *f = fopen(imeIzv, "r");
        write(pip[1], imeOdr, sizeof(imeOdr));
        void *buf = malloc(200);
        while (!feof(f))
        {
            //read(fileno(f), buf, 200);
            //fgets(buf,200,f);
            int i=0;
            while (!feof(f)&&i<200)
            {
                fread(&(buf[i]),1,1,f);
                i++;
            }
            
            //fread(buf,1,200,f);
            write(pip[1], buf, i);
            printf("POSLAO:%s\n",buf);
        }
    }
}