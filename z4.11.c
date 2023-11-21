#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
int main()
{
    int msqid = msgget(10161, 0666 | IPC_CREAT);
    char *s = malloc(5 * sizeof(char));
    sprintf(s, "%d", msqid);
    if (fork() == 0)
    {
        execl("./z4.11a", "./z4.11a", s, NULL);
    }
    else
    {
        if (fork() == 0)
        {
            execl("./z4.11b", "./z4.11b", s, NULL);
        }
        else
        {
            wait(NULL);
            wait(NULL);
            msgctl(msqid, IPC_RMID, NULL);
        }
    }
}