#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{

int sfd,newsfd,s,len,n; char buff[10000];
struct sockaddr_in servaddr,sa;
sfd=socket(AF_INET, SOCK_STREAM,0);
//creates an unnamed socket
if(sfd<0)
{
perror("socket() error:");
exit(-1);
}
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(atoi(argv[1]));
servaddr.sin_addr.s_addr=inet_addr("192.168.0.104");
s=connect(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
//requests for connection with the server(172.16.0.100)
if(s<0)
{
perror("connect() error:");
exit(-1);
} 
printf("ENTER FILE NAME : ");
scanf("%s",buff);
n=strlen(buff);
//read a message from keyboard (i.e. From user)
send(sfd,&buff,n,0);
//writes the message over to the socket from the buffer
printf("enter the public key : ");
scanf("%s",buff);
n=strlen(buff);
send(sfd,&buff,n,0);
//printf("hi");
n=recv(sfd,&buff,10000,0);
buff[n]='\0';
//reads a message from the socket into the buffer
//printf("%s",buff);
FILE *fp=fopen("inputcli.txt","w");
int co;
for(co=0;buff[co]!='\0';co++)
fputc(buff[co],fp);
fclose(fp);
//display the message on the terminal
close(sfd); 
pid_t pid=fork();

if(pid==0)
{
	char private[10];
	printf("enter the private key : ");
	scanf("%s",private);
	execlp("/usr/bin/python","python","rsadec.py","inputcli.txt",private,NULL);
}
else
{
	wait(NULL);
	char buf[1000];int i=0;
	
	FILE *gp=fopen("outputcli.txt","r");
	char c;
	while((c=fgetc(fp))!=EOF)
	{
		buf[i++]=c;
		if(c=='\n')
		{
			buf[i]='\0';
			int a=atoi(buf);
//			printf("%c",(char)a);
		}
	}
}
return 0; 
}
