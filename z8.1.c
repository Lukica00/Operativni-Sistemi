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
int main(int argc, char* argv[])
{
    if(fork()==0)
    {
    }
    else
    {
        if(fork()==0)
        {
        }
        else
        {
        }
    }
}