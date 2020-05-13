#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
    printf("entering main process---\n");
    if(fork() == 0)
    {
        execl("/bin/ls","ls","-l",NULL);
        printf("exiting\n");
    }
    return 0;
}

