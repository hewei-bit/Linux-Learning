#include "main.h"
//图形界面
#include "GUI.h"
//文件IO
#include "IO.h"
//用户和client
#include "user.h"
#include "client_list.h"
#include "thread_pool.h"

CLIENT client_head = NULL;


//线程例程

/* 接收用户上下线提醒 */
void *receive_broadcast(void *arg)//接收广播
{
	int socket_fd = (int)arg;
	char buf[10];
	struct sockaddr_in send_addr;
	socklen_t size = sizeof(send_addr);
	while(1)
	{
		/* 数据收发 */
		bzero(buf, 10);
		recvfrom(socket_fd, buf, 10, 0, (struct sockaddr *)&send_addr, &size);
		printf("from [%s:%d]:%s\n", inet_ntoa(send_addr.sin_addr), ntohs(send_addr.sin_port), buf);
	}
}

/* 接受群聊消息 */
void *receive_group_msg(void *arg)
{
	int socket_fd = (int)arg;
	    //定义send
    char buf[10] = {0};
    struct sockaddr_in send_addr;
    socklen_t len = sizeof(send_addr);
    while(1)
    {
        //数据收发
        bzero(buf,10);
        recvfrom(socket_fd,buf,10,0,(struct sockaddr *)&send_addr,&len);
        printf("from [%s:%d]:%s \n ",inet_ntoa(send_addr.sin_addr),ntohs(send_addr.sin_port),buf);

    }
}

/* 接受普通消息 */
void *receive_msg(void *arg)
{

}

/* 接收文件 */
void *receive_file(void *arg)
{

}

/* 添加用户列表*/
void *add_client_list(void *arg)
{
	// 查找用户是否在列表中

	// 不在则跳过

	// 在则添加

}



int main()
{
	//交互选项
	int num,num_1,num_2;
	//用户登录名和密码
	char username[20] = {0};
	char password[20] = {0};
	//服务器端口和ip
	char server_port[20] = {0};
	char server_ip[20] = {0};
	//用户与client链表
	USER user_head = init_user_list();
	
	client_head = init_client_list();
	//读写buf
	char r_msg[100] = {0};
	char w_msg[100] = {0};
	char file_name[100] = {0};
	char name_buf[100] = {0};
	char name_file_buf[100] = {0};
	//广播
	char broadcast_buf[30] = {0};
	/* 定义文件描述符集合，并且清空 */
	fd_set set;
	FD_ZERO(&set);
	int maxfd = -1;

	//创建线程
    // 1, 初始化一个带有 5 条线程的线程池
    thread_pool *pool = malloc(sizeof(thread_pool));
    init_pool(pool, 5);
    
    // 2, 投入 5 个任务
    // printf("throwing 4 tasks...\n");
	

	// 2.3.接收普通消息
    // add_task(pool, receive_msg, (void *)(rand()%10));
	// 2.4.接收文件
    // add_task(pool, receive_file, (void *)(rand()%10));
	// 2.5.接受新用户并加入链表
	// add_task(pool, add_client_list, (void *)(rand()%10));


	// 从user.txt中读取用户和密码
	ReadUserFromFile(user_head);
	//登录界面
	while(1)
	{
		Login();//注册登录界面
		scanf("%d",&num);
		switch (num)
		{
			case 1:/* 登录界面*/
				printf("/************登录界面************/\n");
				printf("请输入用户名:\n");
				scanf("%s",username);
				printf("请输入密码:\n");
				scanf("%s",password);
				USER login = find_user(user_head,username);
				if(strcmp(login->username,username) == 0)
				{
					if(strcmp(login->password,password) == 0)
					{
						putchar('\n');
						printf("登陆成功\n");


						/* 创建套接字 */
						int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
						if(socket_fd == -1)
						{
							perror("socket() failed:");
							return -1;
						}
						printf("socket() is success!\n");
						maxfd = socket_fd;

						/* 连接服务器 */
						struct sockaddr_in server_addr;
						bzero(&server_addr, sizeof(server_addr));
						printf("请输入服务器端口号:");
						scanf("%s",server_port);
						putchar('\n');
						printf("请输入服务器IP地址:");
						scanf("%s",server_ip);
						putchar('\n');
						server_addr.sin_family = AF_INET;
						server_addr.sin_port = htons(atoi(server_port));
						server_addr.sin_addr.s_addr = inet_addr(server_ip);
						socklen_t len = sizeof(server_addr);
						int connect_ret = connect(socket_fd, (struct sockaddr *)&server_addr, len);
						if(connect_ret == -1)
						{
							perror("connect() failed:");
							return -1;
						}
						printf("connect() is success!\n");

						/* 广播专用 */
						// /* 创建 套接字 */
						// int socket_udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
						// if(socket_udp_fd == -1)
						// {
						// 	perror("socket");
						// 	return -1;
						// }
						
						// /* 绑定IP地址和端口号 */
						// struct sockaddr_in server_udp_addr;
						// bzero(&server_udp_addr, sizeof(server_udp_addr));
						// server_udp_addr.sin_family = AF_INET;
						// server_udp_addr.sin_port = htons(50003);
						// server_udp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
						// int ret = bind(socket_udp_fd, (struct sockaddr *)&server_udp_addr, sizeof(server_udp_addr));
						// if(ret == -1)
						// {
						// 	perror("bind");
						// 	return -1;
						// }
						// printf("bind sucess\n");
						
						// // 添加接收广播的线程
    					// add_task(pool, receive_broadcast, (void *)socket_udp_fd);
						

						/*  实现组播*/
						/* 创建 套接字 */
						// int socket_group_fd = socket(AF_INET, SOCK_DGRAM, 0);
						// if(socket_group_fd == -1)
						// {
						// 	perror("socket");
						// 	return -1;
						// }
						
						// /* 加入多播组 */
						// struct  ip_mreq  mreq;
						// bzero(&mreq, sizeof(mreq));
						// //指明组播IP地址
						// mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.5");
						// //指明接收组播消息的IP地址
						// mreq.imr_interface.s_addr = htonl(INADDR_ANY);
						// //利用刚才信息，将套接字加入组播组
						// setsockopt(socket_group_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq,  sizeof(mreq));

						// 	/* 绑定IP地址和端口号 */
						// struct sockaddr_in server_group_addr;
						// bzero(&server_group_addr, sizeof(server_group_addr));
						// server_group_addr.sin_family = AF_INET;
						// server_group_addr.sin_port = htons(50004);
						// server_group_addr.sin_addr.s_addr = htonl(INADDR_ANY);
						// int ret = bind(socket_group_fd, (struct sockaddr *)&server_group_addr, sizeof(server_group_addr));
						// if(ret == -1)
						// {
						// 	perror("bind");
						// 	return -1;
						// }
						// printf("bind sucess\n");

						// // 2.2.接收群聊消息
						// add_task(pool, receive_group_msg, (void *)socket_group_fd);



						// 通知服务器
						bzero(w_msg, 100);
						sprintf(w_msg,"first time[%s]进入了聊天系统",username);
						write(socket_fd, w_msg, strlen(w_msg));

						/*  下一阶段*/
						while(1)
						{
							/*  显示连接用户*/
							Function_Selection_1(username);
							scanf("%d",&num_1);
							switch (num_1)
							{
								case 1:/* 显示所有连接对象 */
									printf("输入任意字符串即退出\n");
									bzero(w_msg,100);
									sprintf(w_msg,"%s","show_all");
									write(socket_fd,w_msg,strlen(w_msg));
									while (1)
									{
										/* 将socket_fd和STDIN_FILENO加入文件描述符集合 */
										FD_SET(socket_fd, &set);
										FD_SET(STDIN_FILENO, &set);
										maxfd = maxfd > STDIN_FILENO ? maxfd : STDIN_FILENO;
										/* 检测文件描述符是否有动作 */
										select(maxfd+1, &set, NULL, NULL, NULL);
										if(FD_ISSET(socket_fd, &set))//有消息来了
										{
											bzero(r_msg, 100);
											read(socket_fd, r_msg, sizeof(r_msg));
											printf("%s", r_msg);
										}	
										if(FD_ISSET(STDIN_FILENO,&set))
										{
											break;
										}
									}
									break;

								case 2:/* 私聊*/
									printf("请输入你需要通信的对象和信息:(username:msg)\n");
									while(1)
									{
										/* 将socket_fd和STDIN_FILENO加入文件描述符集合 */
										FD_SET(socket_fd, &set);
										FD_SET(STDIN_FILENO, &set);
										maxfd = maxfd > STDIN_FILENO ? maxfd : STDIN_FILENO;
										/* 检测文件描述符是否有动作 */
										select(maxfd+1, &set, NULL, NULL, NULL);

										if(FD_ISSET(STDIN_FILENO, &set))//输入消息
										{
											bzero(w_msg, 100);
											fgets(w_msg, 100, stdin);
											write(socket_fd, w_msg, strlen(w_msg));
											if(strncmp(w_msg, "exit", 4) == 0)
												break;
										}

										if(FD_ISSET(socket_fd, &set))//有消息来了
										{
											bzero(r_msg, 100);
											read(socket_fd, r_msg, sizeof(r_msg));
											printf("%s\n", r_msg);
										}		
									}
									/* 关闭套接字文件描述符 */
									shutdown(socket_fd,2);	
									break;

									case 3:/* 群聊*/
										printf("请输入你需要通信的对象:\n");

										while(1)
										{
											/* 将socket_fd和STDIN_FILENO加入文件描述符集合 */
											FD_SET(socket_fd, &set);
											FD_SET(STDIN_FILENO, &set);
											maxfd = maxfd > STDIN_FILENO ? maxfd : STDIN_FILENO;
											/* 检测文件描述符是否有动作 */
											select(maxfd+1, &set, NULL, NULL, NULL);

											if(FD_ISSET(STDIN_FILENO, &set))//输入消息
											{
												bzero(w_msg, 100);
												fgets(w_msg, 100, stdin);
												write(socket_fd, w_msg, strlen(w_msg));
												if(strncmp(w_msg, "exit", 4) == 0)
													break;
											}

											if(FD_ISSET(socket_fd, &set))//有消息来了
											{
												bzero(r_msg, 100);
												read(socket_fd, r_msg, sizeof(r_msg));
												printf("read:%s\n", r_msg);
											}		
										}

										/* 关闭套接字文件描述符 */
										shutdown(socket_fd,2);	
										
										break;

								case 4:/* 传文件*/
									bzero(w_msg,100);
									bzero(name_buf,100);
									bzero(file_name,100);
									printf("请输入通信的对象:\n");
									scanf("%s",name_buf);
									printf("请输入传输的文件名:\n");
									scanf("%s",file_name);
									sprintf(w_msg,"file-%s-%s",name_buf,file_name);
									
									// 发送文件名
									write(socket_fd,w_msg,strlen(w_msg));

									//打开文件
									int file_fd = open(file_name,O_RDWR);
									if(file_fd == -1)
									{
										perror("open");
										break;
									}

									/* 发送文件 */
									int r, w;
									int nw = 0;
									char r_buf[100] = {0};

									while(1)
									{

									}

									/* 关闭套接字文件描述符 */
									shutdown(socket_fd,2);	
									break;

								case 5:/* 退出 */
									bzero(w_msg, 100);
									sprintf(w_msg,"%s","exit");
									write(socket_fd, w_msg, strlen(w_msg));
									shutdown(socket_fd,2);
									destroy_pool(pool);
									return 0;

								default:
									printf("输入有误请重新输入\n");
									break;

							}
						}
					}
					else//密码有误
						printf("密码错误,请重新输入\n");
				}
				else//用户名有误
					printf("用户名不存在或输入错误,请重新输入\n");
				break;

			case 2:/* 注册 */
				printf("注册\n");
				printf("请输入用户名:\n");
				scanf("%s",username);
				printf("请输入密码:\n");
				scanf("%s",password);
				USER new = new_user_node(username,password);
				printf("你输入的账号密码是:\n");
				show_user_single(new);
				tail_insert_user(user_head,new);
				// list_add(&(new->list),&(user_head->list));
				break;

			case 3:/* .显示当前登录用户 */
				show_user(user_head);
				break;

			case 4:/* 保存登录用户*/
				SaveUserToFile(user_head);
				break;

			case 5:/* 退出 */
				// 销毁线程池
    			destroy_pool(pool);
				return 0;

			default:
				break;
		}
	}
	// 销毁线程池
    destroy_pool(pool);
	return 0;
}