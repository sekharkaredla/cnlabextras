#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
void main(int argc,char *argv[])
{
char buf[100];
int s,len,n;
int sfd=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in servaddr,client;
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(atoi(argv[1]));
servaddr.sin_addr.s_addr=inet_addr("192.168.0.104");
bind(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
listen(sfd,5);
s=accept(sfd,(struct sockaddr*)&client,&len);
while(1)
{
n=recv(s,&buf,100,0);
buf[n]='\0';
if(n==0)
break;
printf("client: %s\n",buf);
int i;
for(i=0;buf[i]!='\0';i++)
	buf[i]=toupper(buf[i]);
send(s,&buf,n,0);
}
close(sfd);
close(s);
}
