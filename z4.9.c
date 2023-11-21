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
    char ime[20];
    int broj;
};
int main()
{
    int msqid = msgget(10161, 0666 | IPC_CREAT);
    if (fork() == 0)
    {
        struct buf *b = malloc(20 * sizeof(struct buf));
        int bi = 0;
        while (1)
        {
            struct buf bu;
            msgrcv(msqid, &bu, sizeof(bu), 1, 0);
            if (!strcmp(bu.ime, "KRAJ") || bi == 19)
                break;
            b[bi] = bu;
            bi++;
        }
        for (int i = 0; i < bi - 1; i++)
        {
            for (int j = i + 1; j < bi; j++)
            {
                if(b[i].broj>b[j].broj){
                    struct buf pom = b[i];
                    b[i]=b[j];
                    b[j]=pom;
                }
            }
        }
        for (int i = 0; i < bi; i++)
        {
            printf("Student %s, %d.\n",b[i].ime,b[i].broj);
        }
    }
    else
    {
        char st[20];
        while (1)
        {
            struct buf b;
            b.mtype = 1;
            scanf("%s", &st);
            strcpy(b.ime, st);
            if (!strcmp(st, "KRAJ"))
            {
                msgsnd(msqid, &b, sizeof(b), 0);
                break;
            }
            int a;
            scanf("%d", &a);
            b.broj = a;
            msgsnd(msqid, &b, sizeof(b), 0);
        }
    }
    msgctl(msqid, IPC_RMID, NULL);
}