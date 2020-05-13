#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc,char **argv)
{
    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        printf("fork error\n");
    }
    else if(pid == 0){
        printf("the return value is %d\n",pid);
        printf("in child process!!\n");
        printf("MY PID is%d\n",getpid());
    }
    else{     
        printf("the return value is %d\n",pid);
        printf("in father process!!\n");
        printf("MY PID is%d\n",getpid());
    }
    return 0;
}
