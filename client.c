#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#define SERVPORT 80
#define MAXDATASIZE 100

void main(int argc,char *argv[]){
	int sockfd,sendbytes;
	char buf[MAXDATASIZE];
	struct hostent *host;
	struct sockaddr_in serv_addr;
	char str[INET_ADDRSTRLEN] = {0x00};

	printf("hello, world!\n");

	if(argc < 2){
		fprintf(stderr,"Please enter the server's hostname!\n");
		exit(1);
	}
	/*地址解析函数*/
	if((host=gethostbyname(argv[1]))==NULL){
		perror("gethostbyname");
		exit(1);
	}

	fprintf(stdout, "offical hostname:%s\n", host->h_name);
	fprintf(stdout, "alias:%s\n", *host->h_aliases);
	fprintf(stdout, "address:%s\n", inet_ntop(host->h_addrtype, *host->h_addr_list, str, sizeof(str)));

	/*创建socket*/
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))== -1){
		perror("socket");
		exit(1);
	}
	/*设置sockaddr_in 结构体中相关参数*/
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERVPORT);
	serv_addr.sin_addr=127.0.0.1;//*((struct in_addr *)host->h_addr);
	bzero(&(serv_addr.sin_zero),8);
	/*调用connect函数主动发起对服务器端的连接*/
	if(connect(sockfd,(struct sockaddr *)&serv_addr,\
				sizeof(struct sockaddr))== -1){
		perror("connect");
		exit(1);
	}
	/*发送消息给服务器端*/
	if((sendbytes=send(sockfd,"hello",5,0))== -1){
		perror("send");
		exit(1);
	}
	while(1){
		recv(sockfd, buf, 3, 0);
		printf("%d\n", buf[0]);
		fflush(stdout);
	}
	close(sockfd);
	pthread_exit(0);
}
