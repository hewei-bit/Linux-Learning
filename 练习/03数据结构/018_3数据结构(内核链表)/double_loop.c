/********************************
	实现双向循环链表的基本操作
********************************/
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};
typedef struct node *NODE;
typedef struct node Node;
//初始化
NODE init_list(void)
{
    NODE head = malloc(sizeof(Node));
    if(NULL == head)
    {
        printf("堆内存申请失败\n");
        return NULL;
    }
    head->next = head->prev = head;
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
void ins_next(NODE p,NODE new)
{
    new->prev = p;
    new->next = p->next;
    p->next = new;
    new->next->prev = new;
}
//查找节点
NODE find_node(NODE head,int data)
{
    NODE p = head->next;
    while(p != head)
    {
        if(p->data == data)
            return p;
        p = p->next;
    }
    return NULL;
}
//删除节点
NODE del_node(NODE p)
{
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->next = p->prev = NULL;
    return p;
} 
//移动节点.将src移动至dest之后
int mv_node(NODE head,int src,int dest)
{
    NODE k = find_node(head,dest);
    if(k == NULL)
    {
        printf("目标节点不存在! \n");
        return -1;
    }
    NODE p = find_node(head,dest);
    if(p == NULL)
    {
        printf("目标节点不存在! \n");
        return -2;
    }

    p = del_node(p);
    ins_next(k,p);
    return 0;
}
//遍历链表
void show(NODE head)
{
    NODE p = head->next;
    while(p != head)
    {
        printf("data: %d \n",p->data);
        p=p->next;
    }
}

int main()
{


    NODE head = init_list();
    if(head == NULL)
    {
        return -1;
    }

    NODE new = new_node(10);
    if(new ==NULL)
        return -1;
    ins_next(head,new);


    new = new_node(20);
    if(new ==NULL)
        return -1;
    ins_next(head,new);

    new = new_node(30);
    if(new ==NULL)
        return -1;
    ins_next(head,new);

    show(head);
    

    int ret = mv_node(head, 20, 30);
	if(ret == 0)
		show(head);
	
	return 0; 
} 