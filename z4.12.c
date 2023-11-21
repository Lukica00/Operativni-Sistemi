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
void recc(char *dir, int lvl, int nivo)
{
    DIR *dr = opendir(dir);
    struct dirent *drnet;
    while ((drnet = readdir(dr)) != NULL)
    {
        if (!strcmp(drnet->d_name, ".") || !strcmp(drnet->d_name, ".."))
            continue;
        struct stat statbuf;
        char* path = calloc(255,sizeof(char));
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
            int i = 0;
            FILE *f = fopen(path, "r");
            while (!feof(f) && i < 10)
            {
                char* s = malloc(10000*sizeof(char));
                int a = 10000;
                getline(&s, (size_t *)&a, f);
                puts(s);
                i++;
                free(s);
            }
        }
        if(S_ISDIR(statbuf.st_mode)&&lvl != nivo){
            recc(path,lvl+1,nivo);
        }
        free(path);
    }
}
int main(int argc, char *argv[])
{
    DIR *dr;
    struct dirent *drnet;
    if (argc != 3)
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
    int nivo = strtol(argv[2], NULL, 10) < 0 ? 0 : strtol(argv[2], NULL, 10);
    recc(argv[1],1,nivo);
    return 0;
}
