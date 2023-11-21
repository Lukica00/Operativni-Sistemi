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
int main(int argc, char *argv[])
{
    int msqid = strtol(argv[1], NULL, 10);
    while (1)
    {
        struct buf bu;
        bu.mtype = 1;
        char s[20];
        scanf("%s", &s);
        strcpy(bu.string,s);
        msgsnd(msqid, &bu, sizeof(bu), 0);
        if (!strcmp(s, "KRAJ"))
            break;
    }
}