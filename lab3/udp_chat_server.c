#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
int main(int argc,char *argv[])
{
int sfd=socket(AF_INET,SOCK_DGRAM,0);
struct sockaddr_in s,server,client;int len,n,i,news,s1;
char buf[1000];
printf("before binding : ip %ld port no %d\n",(long)inet_ntoa(s.sin_addr),ntohs(s.sin_port));
s.sin_family=AF_INET;
s.sin_port=htons(atoi(argv[1]));
s.sin_addr.s_addr=inet_addr("192.168.0.104");
s1=bind(sfd,(struct sockaddr*)&s,sizeof(s));
while(1)
{
	int temp=sizeof(client);
	len=recvfrom(sfd,&buf,1000,0,(struct sockaddr *)&client,&temp);
	printf("client = ");
	printf("%s\n",buf);
	printf("server = ");
	scanf("%s",buf);
	if(!strcmp(buf,"exit"))
	{
	printf("ENDING\n\nBYE");
	exit(-1);
	}
	sendto(sfd,&buf,1000,0,(struct sockaddr *)&client,temp);
}
return 1;
}
