#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int pip[2];
    if (pipe(pip) < 0)
        return -1;
    if (fork() == 0)
    {
        close(pip[1]);
        char ime[80];
        while (read(pip[0],ime,80 * sizeof(char)))
        {
            if(ime[0]>=48 && ime[0]<=57){
                char ime1[80];
                strcpy(ime1,ime); 
                strcat(ime1,"n");
                if(fork()==0){
                    execlp("mv","mv",ime,ime1,NULL);
                }
            }
        }
        close(pip[0]);
        
    }
    else
    {
        close(pip[0]);
        char ime[80];
        scanf("%s", ime);
        while (strcmp(ime, "KRAJ"))
        {
            write(pip[1], ime, 80 * sizeof(char));
            scanf("%s", ime);
        }
        close(pip[1]);
    }
}