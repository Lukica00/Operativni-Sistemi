#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
pthread_t nit1, nit2;

void *Nit1(void *arg)
{
    char *recenica = (char *)arg;
    char **reci = malloc(40 * sizeof(char *));
    int i = 0;
    char *ptr = strtok(recenica, " ");
    while (ptr != NULL)
    {
        reci[i] = ptr;
        ptr = strtok(NULL, " ");
        i++;
    }
    reci[i-1][strlen(reci[i-1])-1]=0;
    for (int j = 0; j < i; j++)
    {
        for (int k = j + 1; k < i; k++)
        {
            if (strcmp(reci[j], reci[k]) < 0)
            {
                char *pom;
                pom = reci[j];
                reci[j] = reci[k];
                reci[k] = pom;
            }
        }
    }
    char *novaRec = malloc(80 * sizeof(char));
    strcpy(novaRec, reci[0]);
    for (int j = 1; j < i; j++)
    {
        strcat(novaRec, " ");
        strcat(novaRec, reci[j]);
    }
    free(reci);
    return (void *)novaRec;
}
void *Nit2(void *arg)
{
    void *recenicaVoid;
    pthread_join(nit1, &recenicaVoid);
    int q = 1;
    char *recenica = (char *)recenicaVoid;
    while (recenica[q] != 0)
    {
        recenica[q] = tolower(recenica[q]);
        q++;
    }
    recenica[0] = toupper(recenica[0]);
    puts(recenica);
    free(recenicaVoid);
}

int main()
{
    char *recenica = malloc(80 * sizeof(char));
    fgets(recenica, 80, stdin);
    pthread_create(&nit1, NULL, Nit1, (void *)recenica);
    pthread_create(&nit2, NULL, Nit2, NULL);
    pthread_join(nit2, NULL);
    free(recenica);
    printf("KRAJ");
}