#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
struct buf
{
    long mtype;
    char string[20];
};
int main(int argc, char* argv[]){
    int msqid = strtol(argv[1],NULL,10);
    while (1)
        {
            struct buf bu;
            msgrcv(msqid, &bu, sizeof(bu), 1, 0);
            if (!strcmp(bu.string, "KRAJ"))
                break;
            printf("%s\n",bu.string);
        }
}