#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SPACE  0
#define DATA 1


#define SIZE 100

union semun//自定义信号联合体
{
    int val;
};

static void sem_p(int semid,int semnum)//P操作
{
    struct sembuf op[1];
    op[0].sem_num = semnum;
    op[0].sem_op = -1;
    op[0].sem_flg = 0;
    semop(semid,op,1);
}

static void sem_v(int semid,int semnum)//v操作
{
    struct sembuf op[1];
    op[0].sem_num = semnum;
    op[0].sem_op = 1;
    op[0].sem_flg = 0;
    semop(semid,op,1);
}
//初始化
static void seminit(int semid,int semnum,int value)
{
    union semun a;
    a.val = value;
    semctl(semid,semnum,SETVAL,a);
}
//获取进程名进程号
int pid()
{
	FILE *fp = popen("ps -e | grep \'jack\' | awk \'{print $1}\'", "r");//打开管道，执行shell 命令
    char buffer[10] = {0};
    int pid;
    while (NULL != fgets(buffer, 10, fp)) //逐行读取执行结果并打印
    {
       // printf("PID:  %s", buffer);
        pid = atoi(buffer);
        //printf("pid:%d\n", pid);
    }
    
    pclose(fp); //关闭返回的文件指针，与popen配套使用,注意不是用fclose噢
	return pid;
}


int main(int argc, char **argv[])
{
	printf("rose pid : %d \n",getpid());
	//1.获取键值
    key_t key1 = ftok(".",3);
    printf("key 1: %d \n",key1);
    key_t key2 = ftok(".",4);
    printf("key 2: %d \n",key2);
	// key_t key3 = ftok(".",5);
    // printf("key 3: %d \n",key3);


    //2.创建共享内存
    int shm_id = shmget(key1,1024,IPC_CREAT|0666);
    if(-1 == shm_id)
    {
        perror("shmget");
        return -1;
    }
	// int shm_id_1 = shmget(key3,1024,IPC_CREAT|0666);
    // if(-1 == shm_id)
    // {
    //     perror("shmget");
    //     return -1;
    // }

    //3.映射至内存空间
    char *addr = shmat(shm_id,NULL,0);
    bzero(addr,1024);
    char rose_buf[SIZE];
    bzero(rose_buf,SIZE);
    //char i = 0;
	// char *addr_1 = shmat(shm_id_1,NULL,0);
    // bzero(addr_1,1024);
    // char rose_buf_1[SIZE];
    // bzero(rose_buf_1,SIZE);

    //4.创建一个信号量
    int sem_id = semget(key2,2,IPC_CREAT|0666);
    if( sem_id > 0)
    {
        //5.初始化信号量
        seminit(sem_id,SPACE,0);
        seminit(sem_id,DATA,1);
    }
    else
    {
        sem_id = semget(key2,2,0664);
    }

	// int sem_id_1 = semget(key3,2,IPC_CREAT|0666);
	// seminit(sem_id_1,SPACE,1);
    // seminit(sem_id_1,DATA,0);


    //5.获取jack的pid
	// int pid ;
    // printf("pid : ");
    // scanf("%d",&pid);
    // getchar();

	while(1)
	{
		//申请数据资源-1
		sem_p(sem_id,DATA);
        //读数据

        if(strlen(addr)!=0)
		    printf("from jack: %s \n",addr);

        printf("rose:");
        fgets(addr,1024,stdin);
        bzero(rose_buf,SIZE);
		strcpy(rose_buf,addr);
		if(strncmp(rose_buf,"exit",4)==0)
            break;
        //释放空间资源	+1
		sem_v(sem_id,SPACE);


		


		// // 申请空间资源
        // sem_p(sem_id_1,SPACE);
        // //写数据
        // printf("rose:");
        // fgets(rose_buf_1,SIZE,stdin);
        // //增加数据资源
        // sem_v(sem_id_1,DATA);

		// bzero(rose_buf_1,SIZE);
		// strcpy(rose_buf_1,addr_1);
		// if(strncmp(rose_buf_1,"exit",4)==0)
        //     break;
        
		// sleep(2);
	}
		
	    //解除映射
    shmdt(addr);
	// shmdt(addr_1);
    //删除共享内存
    shmctl(shm_id,IPC_RMID,NULL);
	// shmctl(shm_id_1,IPC_RMID,NULL);

	// semctl(sem_id_1,IPC_RMID,0);
	semctl(sem_id,IPC_RMID,0);


	return 0;
}