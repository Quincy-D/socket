#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define SERVPORT 8080
#define BACKLOG 10
#define MAX_CONNECTED_NO 10
#define MAXDATASIZE 5
int main()
{
	struct sockaddr_in server_sockaddr,client_sockaddr;
	int sin_size,recvbytes;
	int sockfd,client_fd;
	char buf[MAXDATASIZE];
	/*建立socket连接*/
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))== -1){
		perror("socket");
		exit(1);
	}
	printf("socket success!,sockfd=%d\n",sockfd);
	/*设置sockaddr_in 结构体中相关参数*/
	server_sockaddr.sin_family=AF_INET;
	server_sockaddr.sin_port=htons(SERVPORT);
	server_sockaddr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(server_sockaddr.sin_zero),8);//其余部分置零
	/*绑定函数bind*/
	if(bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(struct
					sockaddr))== -1){
		perror("bind");
		exit(1);
	}
	printf("bind success!\n");
	/*调用listen函数*/
	if(listen(sockfd,BACKLOG)== -1){
		perror("listen");
		exit(1);
	}
	printf("listening....\n");
	/*调用accept函数，等待客户端的连接*/
	if((client_fd=accept(sockfd,(struct sockaddr *)&client_sockaddr,&sin_size))== -1){
		perror("accept");
		exit(1);
	}
	/*调用recv函数接收客户端的请求*/
	if((recvbytes=recv(client_fd,buf,MAXDATASIZE,0))== -1){
		perror("recv");
		exit(1);
	}
	printf("received a connection :%s\n",buf);
	close(sockfd);
}
