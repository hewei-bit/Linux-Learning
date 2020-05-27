#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void fun(int sig)
{
    printf("pid: %d.sig:%d \n",getpid(),sig);
}

int main()
{
    int i = 0;
    int ret;
   
    // signal(SIGINT,SIG_IGN);
    //signal(SIGINT,fun);

    pid_t pid = fork();
    
    //子进程
    if(pid ==0)
    { 
        // ret = pause();
        signal(SIGUSR1,fun);
        signal(SIGUSR2,fun);
        signal(SIGINT,fun);

        while(1)
        {
            printf("s_pid: %d ,i : %d\n",getpid(),++i);
            sleep(1);       
            // ret = raise(SIGUSR1);
            // if(0 == ret)
            // {
            //     printf("raise  is called\n");
            // }
        }
    }
     
    //父进程
    if(pid>0)
    {
    
        sleep(4);

        //ret = kill(pid,SIGINT);
        kill(pid,SIGINT);
        kill(pid,SIGUSR2);
        printf("signal send \n");
    }

}