#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int dat[2];
    int r;
    if (pipe(dat) == -1)
    {
        printf("Greska prilikom kreiranja datavoda!\n");
        return -1;
    }

    if(fork()!=0){
        close(dat[0]);
        for (int i = 0; i < 50; i++)
        {
            r = rand();
            write(dat[1],&r,sizeof(r));
        }
        close(dat[1]);
        return 0;
    }

    if(fork()!=0){
        close(dat[1]);
        for (int i = 0; i < 50; i++)
        {
            read(dat[0],&r,sizeof(r));
            printf("%d ",r);
        }
        close(dat[0]);
        return 0;
    }
}