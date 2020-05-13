#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




int main()
{
    int fd;
    int ret;
    fd = open("hole.txt",O_WRONLY|O_CREAT|O_TRUNC,0664);
    if(fd ==-1)
    {
        ERR_EXIT("open error");
    }
    write(fd,"hello",5);
    ret = lseek(fd,1024*1024,SEEK_CUR);
    if(ret == -1)
        ERR_EXIT("lseek error");
    write(fd,"world",5);
    close(fd);
    return 0;
}
