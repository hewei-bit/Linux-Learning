#include "head.h"

struct client
{
	char ip[30];
	unsigned short port;
	int accept_fd;
	struct list_head list;//内核链表小结构体
};//分号

struct client *head = NULL;

/* 初始化链表 */
struct client *init_list(void)
{
	struct client *head = malloc(sizeof(struct client));
	if(head != NULL)
	{
		INIT_LIST_HEAD(&head->list);
	}
	return head;
}

int main(int argc,char **argv)
{
	// if(argc != 2)
	// {
	// 	printf("%s [htons]\n", argv[0]);
	// 	return -1;
	// } 

	/* 创建 套接字 */
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		perror("socket");
		return -1;
	}
	
	/* 绑定IP地址和端口号 */
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(50002);
	server_addr.sin_addr.s_addr = inet_addr("192.168.3.166");
	// server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}
	printf("bind sucess\n");
	
	/* 设置监听 这个套接字只负责链接 */
	ret = listen(socket_fd, 2);
	if(ret == -1)
	{
		perror("listen");
		return -1;
	}
	printf("listen sucess\n");
	
	/* 等待对方链接 */
	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr));
	socklen_t size = sizeof(client_addr);
	int accept_fd = -1;
	// int cfd_1 = accept(socket_fd, (struct sockaddr *)&client_addr, &size);
	// if(cfd_1 == -1)
	// {
	// 	perror("accept");
	// 	return -1;
	// }
	// printf("accept sucess\n");
	
	//定义文件描述符集合,并且清空
	fd_set set;
	FD_ZERO(&set);
	int maxfd = socket_fd;
	struct list_head *pos,*n;
	struct client *tmp,*temp;
	char *str = NULL;
	char msg[100] = {0};

	while(1)
	{
		//将监听套接字加入集合
		FD_SET(socket_fd,&set);

	}
	
	
	/* 关闭套接字文件描述符 */
	close(accept_fd);
	close(socket_fd);
	
	return 0;
}