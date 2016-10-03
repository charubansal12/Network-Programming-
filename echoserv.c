/*TCP Server Code for chat*/
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

int main()
{
	char sendline[100];
	char recvline[100];
	int listenfd,connfd;
	
	struct sockaddr_in servaddr;
	listenfd=socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(22000);

	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	listen(listenfd,10);
	connfd=accept(listenfd,(struct sockaddr *)NULL,NULL);
	
	while(1)
	{
		bzero(sendline,100);
		bzero(recvline,100);
		read(connfd,recvline,100);
		printf("Client - %s",recvline);
		
		fgets(sendline,100,stdin);
		write(connfd,sendline,strlen(sendline)+1);
	}
	return 0;
}
