#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>
int main(int argc, char **argv)
{
	char **vgra = (char**) malloc((argc)*sizeof(char*));
	for (int i = 2; i < argc; i++)
	{
		vgra[argc - i - 1] = (char *)malloc(strlen(argv[i]) * sizeof(char));
		strcpy(vgra[argc - i - 1], argv[i]);
	}
	vgra[argc - 2]=NULL;
	if(fork()==0)
	{
		printf("%d \n",execv(argv[1], vgra));
	}
	else
	{
		wait(NULL);
	}
}