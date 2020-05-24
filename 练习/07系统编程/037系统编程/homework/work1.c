//使用进程创建API，创建一个进程扇，每个子进程打印自己的PID后退出，父进程最后结束。
//要求：实现父进程比子进程先打印PID（pid一般是递增）
//	     实现子进程比父进程先打印PID（pid一般是递减）

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc,char **argv)
{
    int count;
    if(argc < 2)
        count = 2;
    else
        count = atoi(argv[1]);

    int i;
    pid_t pid;
    for(i = 1;i < count;i++)
    {
         pid= fork();
         if(pid < 0)
         {
             perror("fork error");
             exit(1);
         }
         else if(pid > 0)
         {
             wait(NULL);
            printf("pid : %d,ppid : %d \n",getpid(),getppid());
             break;//父进程退出循环，子进程继续做循环
         }
    }

//     if(pid > 0)
//     {
//          int a;
//          sleep(1);
//          wait(&a);
//     }
//    printf("pid : %d,ppid : %d \n",getpid(),getppid());

    exit(0);
    //return 0;
}