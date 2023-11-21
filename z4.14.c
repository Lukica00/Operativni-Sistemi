#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <dirent.h>
#include <sys/stat.h>
struct fajl
{
    char ime[256];
    int velicina;
};
struct fajl niz[100];
int i = 0;
void recc(char *dir)
{
    DIR *dr = opendir(dir);
    struct dirent *drnet;
    while ((drnet = readdir(dr)) != NULL)
    {
        if (!strcmp(drnet->d_name, ".") || !strcmp(drnet->d_name, ".."))
            continue;
        struct stat statbuf;
        char *path = calloc(255, sizeof(char));
        strcat(path, dir);
        strcat(path, "/");
        strcat(path, drnet->d_name);
        if (stat(path, &statbuf) < 0)
        {
            printf("Nema");
            continue;
        }
        if (S_ISREG(statbuf.st_mode))
        {
            if (statbuf.st_size > 1 * 1024)
            {
                struct fajl a;
                strcpy(a.ime, drnet->d_name);
                a.velicina = statbuf.st_size;
                niz[i] = a;
                i++;
            }
        }
        if (S_ISDIR(statbuf.st_mode))
        {
            recc(path);
        }
    }
}
int main(int argc, char *argv[])
{
    DIR *dr;
    struct dirent *drnet;
    if (argc != 2)
    {
        printf("Nema");
        exit(0);
    }
    if (argv[1][0] != '/')
    {
        printf("Nema");
        exit(0);
    }
    if ((dr = opendir(argv[1])) == NULL)
    {
        printf("Nema");
        exit(0);
    }
    recc(argv[1]);
    for (int j = 0; j < i - 1; j++)
    {
        for (int k = j + 1; k < i; k++)
        {
            if (niz[j].velicina > niz[k].velicina)
            {
                struct fajl pom = niz[j];
                niz[j] = niz[k];
                niz[k] = pom;
            }
        }
    }
    for (int j = 0; j < i; j++)
    {
        printf("Ime: %s, Velicina:%d\n", niz[j].ime, niz[j].velicina);
    }
    return 0;
}
