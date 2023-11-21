#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int cc = 0, cz = 0;
void ctrlc(int a)
{
    signal(SIGINT, ctrlc);
    cz = 0;
    if (++cc == 5)
        exit(0);
}
void ctrlz(int z)
{
    signal(SIGTSTP, ctrlz);
    if (++cz == 2)
    {
        printf("\"Control+c\" pritisnuto %d puta.\n", cc);
        cc = 0;
    }
}
int main()
{
    signal(SIGINT, ctrlc);
    signal(SIGTSTP, ctrlz);
    while (1)
        pause();
}
