#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    char *p = (char *)calloc(25,4);
    if(p == NULL) 
    {
        printf("malloc err \n");
        return -1;
    }

    scanf("%s",p);
    printf("%s \n",p);
    printf("sizeof(p): %ld \n",sizeof(p));
    printf("%p \n",p);
    return 0;

}