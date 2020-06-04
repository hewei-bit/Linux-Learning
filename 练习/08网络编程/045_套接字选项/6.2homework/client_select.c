#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		
	}

	/* 创建 套接字 */
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		perror("socket");
		return -1;
	}
	
	/* 链接服务器 */
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(50002);
	server_addr.sin_addr.s_addr = inet_addr("192.168.3.166");
	int ret = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(ret == -1)
	{
		perror("connect");
		return -1;
	}
	//定义文件描述符集合
	fd_set set;
	FD_ZERO(&set);
	int maxfd = socket_fd;

	char r_msg[100] = {0};
	char w_msg[100] = {0};


	while(1)
	{
		//将socket_fd和STDIN_FILENO加入集合
		FD_SET(socket_fd,&set);
		FD_SET(STDIN_FILENO,&set);
		maxfd = maxfd>STDIN_FILENO?maxfd : STDIN_FILENO;
		//检测文件是否有动作
		seleect(maxfd+1,&set,NULL,NULL,NULL);
		//输入消息
		if(FD_ISSET(STDIN_FILENO,&set))
		{
			bzero(w_msg,0);
			fgets(w_msg,100,stdin);
			write(socket_fd,w_msg,strlen(w_msg));
			if(strncmp(w_msg,"exit",4) == 0)
			{
				break;
			}
		}
		//有消息来了
		if(FD_ISSET(socket_fd,&set))
		{
			bzero(r_msg[100],0);
			ret = read(socket_fd,r_msg,sizeof(r_msg));
			printf("ret:%d, buf:%s\n", ret, r_msg);
		}
		
	}
	
	
	/* 关闭套接字文件描述符 */
	// close(socket_fd);
	shutdown(socket_fd,2);
	return 0;
}