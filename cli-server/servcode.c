#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define MAXLINE 1024

void err_quit(const char* x)
{
	perror(x);
	exit(1);
}

/*
//This is the original function for echo server.
void str_echo(int sockfd)
{
	ssize_t n;
	char line[MAXLINE];
	for(;;){
		if((n=read(sockfd,line,MAXLINE))==0)
			return;
		write(sockfd,line,n);
	}
}*/

void str_echo(FILE *fp,int sockfd)
{
	char recvline[MAXLINE], sendline[MAXLINE];
	char serv[4];
	serv[0]='S';
	serv[1]=':';
	serv[2]='\t';

	for(;;){
		fgets(sendline,MAXLINE,fp);
		fputs(recvline,stdout);	
		fputs(serv,stdout);
		fputs(sendline,stdout);
		if((read(sockfd,recvline,MAXLINE))==0)
			return;
		write(sockfd,serv,strlen(serv));
		write(sockfd,sendline,strlen(sendline));
		
	}
		
}

int main()
{
	int listenfd,connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(22000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(listenfd,10);
	
	for(;;){
		clilen=sizeof(cliaddr);
		connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
		
		if((childpid=fork())==0) {
			close(listenfd);
			//str_echo(connfd);
			str_echo(stdin,connfd);
			exit(0);
		}

		close(connfd);
	}
	return 0;
}
