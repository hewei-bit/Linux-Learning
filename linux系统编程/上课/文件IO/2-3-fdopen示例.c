#include <stdio.h>


int main(int argc,cahr** argv[])
{
    FILE *fp;
    int fd;
    if((fp = fopen("hello.txt","w+"))==NULL)
    {
        printf("fopen file error\n");
        return 0;
    }
    fprintf(fp,"hello world\n");
    fclose(fp);
    if((fd = open("hello.txt",O_RDWR))== -1)
    {
        printf("open file fail\n");
        return 0;
    }
    if((fp = fdopen(fd,"a+"))==NULL)
    {
        printf("fdopen open\n");
        return 0;
    }
    fprintf(fp,"linuc C Program\n");
    fclose(fp);
    
}


