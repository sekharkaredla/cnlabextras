#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
void main(int argc,char *argv[])
{
int sfd,s,len,n;char buf[100];
struct sockaddr_in servaddr,server;
sfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(atoi(argv[1]));
servaddr.sin_addr.s_addr=inet_addr("192.168.0.104");
connect(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
int n1;
printf("enter the number of messages : ");
scanf("%d",&n1);int i;
for(i=0;i<n1;i++)
{
printf("enter a message :");
scanf("%s",buf);
n=strlen(buf);
send(sfd,&buf,n,0);
n=recv(sfd,&buf,100,0);
buf[n]='\0';
printf("%s\n",buf);
}
}
