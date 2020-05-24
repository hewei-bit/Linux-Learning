/**************************
实现一个单链表，保存学生的姓名，学号，年龄。
要求：
输入1，新建节点保存一个学生的信息，并按照学号插入到链表中（学号按照升序排列）
输入2，再输入学号，找到该学生的信息节点，打印并删除
输入3，顺序打印链表中每位同学的信息
输入4，逆序打印链表中每位同学的信息
输入5，退出程序

时间：2020-4-22 
**************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _STU
{
    char name[10];
    int id;
    int age;
    struct _STU *next;
}StuNode,*STUNODE;

//初始化链表
STUNODE init_node(void)
{
    STUNODE head = malloc(sizeof(StuNode));
    if(head == NULL)
    {
        printf("init err \n");
        return NULL;
    }
    memset(head,0,sizeof(StuNode));
    head->next = NULL;
    return head;
}

//新节点
STUNODE new_node(char *name,int id,int age )
{
    STUNODE new = malloc(sizeof(StuNode));
    if(new == NULL)
    {
        printf("new err \n");
        return NULL;
    }
    new->age = age;
    new->id = id;
    strcpy(new->name,name);
    new->next = NULL;
}
//查找节点
STUNODE search_node(STUNODE head, int id)
{
    STUNODE p = head->next;
    while (p)
    {
        if(p->id == id)
            break;
        p = p->next;
    }
    return p;   
}
//删除节点
STUNODE del_node(STUNODE head,int id)
{
    STUNODE p = search_node(head,id);
    if(NULL == p)
        return NULL;
    while(head->next != p)
        head = head->next;

    head->next = p->next;
    p->next = NULL;

    return p;
}
//按学号插入链表
int insert_node(STUNODE head,STUNODE new)
{
    if(head->next == NULL)
    {
        head->next = new;
        return 0;
    }
    STUNODE p = head->next;
    STUNODE k = head;
    while(p->id <= new->id)
    {
        if(p->next == NULL)
        {
            p->next = new;
            return 0;
        }
        p = p->next;
    }

    while(k->next != p)
        k = k->next;

    new->next = p;
    k->next = new;
    return 0;
}




//顺序打印

//倒序打印
void show_reverse(STUNODE head)
{
    if(head->next != NULL)
        show_reverse(head->next);
    if(head->name[0] != 0)
        printf("学号:%5d 姓名: %5s年龄:%5d \n",head->id,head->name,head->age);
}



//遍历
void show(STUNODE head)
{
    STUNODE p = head->next;
    while(p)
    {
        printf("学号:%5d 姓名: %5s年龄:%5d \n \n",p->id,p->name,p->age);
        p = p->next;
    }
}


int main()
{
    STUNODE head = init_node();
    if(head == NULL)
    {
        printf("list init err \n");
        return -1;
    }

    int id;
    int num;
    int age;
    char name[10] = {0};

    while(1)
    {
        printf("请输入选项\n");
        printf("输入1，新建节点保存一个学生的信息，并按照学号插入到链表中（学号按照升序排列）\n");
        printf("输入2，再输入学号，找到该学生的信息节点，打印并删除\n");
        printf("输入3，顺序打印链表中每位同学的信息\n");
        printf("输入4，逆序打印链表中每位同学的信息\n");
        printf("输入5，退出程序\n");
    
        scanf("%d",&num);
        switch (num)
        {
        case 1:
            printf("输入姓名 学号 年龄：\n");
            scanf("%s %d %d",name,&id,&age);
            STUNODE new = new_node(name,id,age);
            if(new == NULL)
            {
                printf("new node err \n");
                return -2;
            }
            insert_node(head,new);
            
            break;
        case 2:
            /* code */
            break;
        case 3:
            show(head);
            break;
        case 4:
            show_reverse(head);
            break;
        case 5:
            return 0;
            break;
        default:
            printf("输入选项无效，请重新输入\n");
            break;
        }
    }
    return 0;
}














