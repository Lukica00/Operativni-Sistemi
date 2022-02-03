#include <sys/msg.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
struct mymsgbuf
{
    long mtype;
    int broj;
};
int main(int argc, char *argv[])
{
    int msqid = msgget(12345, 0666 | IPC_CREAT);
    if (fork() == 0)
    {
        for (int i = 0; i < 25; i++)
        {
            struct mymsgbuf buf;
            msgrcv(msqid, &buf, sizeof(buf), 1, 0);
            FILE* f = fopen("rezultat.txt","a");
            fprintf(f,"%d ",buf.broj*3);
            fclose(f);
        }
        
    }
    else
    {
        for (int i = 0; i < 25; i++)
        {
            struct mymsgbuf buf;
            int a;
            scanf("%d",&a);
            buf.broj = a;
            buf.mtype = 1;
            msgsnd(msqid, &buf, sizeof(buf), 0);
        }
        wait(NULL);
        msgctl(msqid, IPC_RMID, NULL);
    }
}