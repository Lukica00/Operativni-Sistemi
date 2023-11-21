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
#include <errno.h>
int main(int argc, char const *argv[])
{
    DIR *dr1;
    DIR *dr2;
    if (argc != 3)
    {
        printf("Nema1");
        exit(0);
    }
    if (argv[1][0] != '/')
    {
        printf("Nema2");
        exit(0);
    }

    if (argv[2][0] != '/')
    {
        printf("Nema3");
        exit(0);
    }
    if ((dr1 = opendir(argv[1])) == NULL)
    {
        printf("Nema4");
        exit(0);
    }
    if ((dr2 = opendir(argv[2])) == NULL)
    {
        printf("Nema5");
        exit(0);
    }
    struct dirent *drnet1;
    while ((drnet1 = readdir(dr1)) != NULL)
    {
        if (!strcmp(drnet1->d_name, ".") || !strcmp(drnet1->d_name, ".."))
            continue;
        int q = 0;
        struct stat statbuf1;
        char *path1 = calloc(255, sizeof(char));
        strcat(path1, argv[1]);
        strcat(path1, "/");
        strcat(path1, drnet1->d_name);
        if (stat(path1, &statbuf1) < 0)
        {
            printf("Nema6");
            free(path1);
            continue;
        }
        if (!S_ISREG(statbuf1.st_mode))
        {
            free(path1);
            continue;
        }
        struct dirent *drnet2;
        while ((drnet2 = readdir(dr2)) != NULL)
        {
            if (!strcmp(drnet2->d_name, ".") || !strcmp(drnet2->d_name, ".."))
                continue;
            struct stat statbuf2;
            char *path2 = calloc(255, sizeof(char));
            strcat(path2, argv[2]);
            strcat(path2, "/");
            strcat(path2, drnet2->d_name);
            if (stat(path2, &statbuf2) < 0)
            {
                printf("Nema7 %s::::%d\n",drnet2->d_name,errno);
                free(path2);
                continue;
            }
            if (!S_ISREG(statbuf2.st_mode))
            {
                free(path2);
                continue;
            }
            if (!strcmp(drnet1->d_name, drnet2->d_name) && statbuf1.st_size == statbuf2.st_size)
            {
                q = 1;
                free(path2);
                break;
            }
            free(path2);
        }
        if (q == 0)
        {
            char *path2 = calloc(255, sizeof(char));
            if (fork() == 0)
            {
                strcat(path2, argv[2]);
                strcat(path2, "/");
                strcat(path2, drnet1->d_name);
                execlp("cp", "cp", path1, path2, NULL);
            }
            free(path2);
        }
        free(path1);
    }

    return 0;
}
