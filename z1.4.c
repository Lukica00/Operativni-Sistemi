#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
void *fja(void *arg)
{
    int k = *(int *)arg;
    for (int i = 0; i < k; i++)
    {
        printf("%d", i);
        fflush(stdout);
        sleep(3);
    }
    printf("%d", k);
    fflush(stdout);
    printf("\n");
}
int main()
{
    pthread_t nit;
    while (1)
    {
        char *s;
        scanf("%s", s);
        if (!strcmp(s, "KRAJ"))
            break;
        int p = atoi(s);
        pthread_create(&nit, NULL, (void *)fja, (void *)&p);
        pthread_join(nit, NULL);
    }
}
