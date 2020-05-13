typedef struct styInfo{
    char stuName[10];
    int Age;
}ElemType;

typedef struct node{
    ElemType data;
    struct node *next;
}ListNode,*ListPtr;


int main(int argc,char argv[])
{
    while(1)
    {
        printf("1 Create List\n");
        printf("2 print List\n");
        printf("3 Insert List\n");
        printf("4 Qiut\n");
        char command = getchar();
        switch(command)
        {
            case '1':ListHead = CreateList();break;
            case '2':ListHead = PrintList();break;
            case '3':ListHead = InsertList();break;
            case '4':return 0;
        }
    }
    return 0;
}



