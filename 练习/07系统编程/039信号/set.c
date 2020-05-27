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

        signal(SIGUSR1,fun);
        signal(SIGUSR2,fun);
        signal(SIGINT,fun);

        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set,SIGUSR2);
        sigaddset(&set,SIGUSR1);
        sigaddset(&set,SIGINT);

        sigprocmask(SIG_BLOCK,&set,NULL);

        raise(SIGUSR2);
        raise(SIGUSR1);
        raise(SIGINT);
        printf("send signal err \n");

        sleep(2);

        sigprocmask(SIG_UNBLOCK,&set,NULL);


        sleep(2);


}