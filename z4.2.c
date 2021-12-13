#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argv, char* argc[]){
    int pip[2];
    char* ime = argc[1];
    int N = atoi(argc[2]);
    if(pipe(pip)<0)return -1;
    if(fork()==0){
        close(pip[0]);
        fclose(stdout);
        dup2(pip[1],1);
        execl(ime,ime,NULL);
    }else{
        close(pip[1]);
        char buf;
        int  i = 0;
        while(read(pip[0],&buf,sizeof(char))){
            printf("%c",buf);
            fflush(stdout);
            if(buf=='\n'){
                i++;
                if(i==N){
                    i=0;
                    printf("-MORE-\n");
                    getc(stdin);
                }
            }
        }
    }
}