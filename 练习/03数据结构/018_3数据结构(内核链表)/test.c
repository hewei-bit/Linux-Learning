/********************************
	实现双向循环链表的基本操作
********************************/
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
}Node,*NODE;

//初始化
NODE init_list(void)
{
    NODE head = malloc(sizeof(Node));
    if(NULL == head)
    {
        printf("堆内存申请失败\n");
        return NULL;
    }
    return head;
}

//建立新节点
NODE new_node(int data)
{
    NODE new = malloc(sizeof(Node));
    if(NULL == new)
    {
        printf("堆内存申请失败\n");
        return NULL;
    }
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    return new;
}
//将新节点插入p之后
void 
//查找节点

//删除节点

//移动节点.将src移动至dest之后

//遍历链表





int main(int agrc,char **argv)
{


}