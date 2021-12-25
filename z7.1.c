#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
struct mymsgbuf
{
    long mtype;
    char mtext[20];
};
int main(int argc, char *argv[])
{
    int msqid = msgget(10161, 0666 | IPC_CREAT);
    if (fork() != 0)
    {
        int i = 0;
        struct mymsgbuf buf;
        while (1)
        {
            msgrcv(msqid, &buf, sizeof(buf), 1, 0);
            if (!strcmp(buf.mtext, "KRAJ"))
                break;
            int j = 0;
            int k = 0;
            while (buf.mtext[j] != 0)
            {
                if (buf.mtext[j] >= 'A' && buf.mtext[j] <= 'Z')
                    k++;
                j++;
            }
            struct mymsgbuf buf1;
            buf1.mtype = 2;
            char bb[2];
            sprintf(bb, "%d", i);
            strcpy(buf1.mtext, bb);
            strcat(buf1.mtext, "-");
            sprintf(bb, "%d", k);
            strcat(buf1.mtext, bb);
            msgsnd(msqid, &buf1, sizeof(buf1), 0);
            i++;
        }

        struct mymsgbuf buf1;
        buf1.mtype = 2;
        strcpy(buf1.mtext, "KRAJ");
        msgsnd(msqid, &buf1, sizeof(buf1), 0);

        buf.mtype = 1;
        msgrcv(msqid, &buf, sizeof(buf), 1, 0);
    }
    else
    {
        FILE *f = fopen(argv[1], "r");
        while (!feof(f))
        {
            struct mymsgbuf buf;
            buf.mtype = 1;
            fgets(buf.mtext, 20, f);
            msgsnd(msqid, &buf, sizeof(buf), 0);
        }
        fclose(f);
        struct mymsgbuf buf;
        buf.mtype = 1;
        strcpy(buf.mtext, "KRAJ");
        msgsnd(msqid, &buf, sizeof(buf), 0);

        struct mymsgbuf buf1;
        buf1.mtype = 2;
        while (1)
        {
            msgrcv(msqid, &buf1, sizeof(buf1), 2, 0);
            printf("%s\n", buf1.mtext);
            if (!strcmp(buf1.mtext, "KRAJ"))
                break;
        }

        msgsnd(msqid, &buf, sizeof(buf), 0);
    }
    msgctl(msqid, IPC_RMID, NULL);
}