#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define FILE_PATH "./test.txt"

int main(void)
{
    char buf[100];
    int num = 0;
    int fd;
    if((num = read(STDIN_FILENO,buf,10))==-1)
    {
        printf("read error\n");
        exit(-1);
    }
    else{
        write(STDOUT_FILENO,buf,num);
    }
    return 0;
}
