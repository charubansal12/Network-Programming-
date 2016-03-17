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
//original code
void str_cli(FILE *fp,int sockfd)
{
	char sendline[MAXLINE],recvline[MAXLINE];

	while(fgets(sendline,MAXLINE,fp)!=NULL)	{
		write(sockfd,sendline,1);
		sleep(1);
		write(sockfd,sendline+1,strlen(sendline)-1);

		if(read(sockfd,recvline,MAXLINE) == 0)
			err_quit("str_cli : server terminated prematurely");
		fputs(recvline,stdout);
	}
}*/

void str_cli(FILE *fp,int sockfd)
{

	//fflush(stdin);
	char sendline[MAXLINE],recvline[MAXLINE];
	char cli[4];
	cli[0]='C';
	cli[1]=':';
	cli[2]='\t';
	for(;;){
		fgets(sendline,MAXLINE,fp);
	  	write(sockfd,cli,strlen(cli));
		write(sockfd,sendline,strlen(sendline));

		if(read(sockfd,recvline,MAXLINE)==0)
			err_quit("str_cli : server terminated prematurely");
		
		fputs(cli,stdout);
		fputs(sendline,stdout);
		fputs(recvline,stdout);
		
	}
}
int main()
{
	int sockfd;
	struct sockaddr_in servaddr;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(22000);
	inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
	
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	str_cli(stdin,sockfd);
	exit(0);
}
