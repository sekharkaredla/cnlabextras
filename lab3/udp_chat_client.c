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
//strcpy(buf,argv[2]);
//itoa(inet_ntoa(s.sin_addr),buf);
printf("before binding : ip %ld port no %d\n",(long)inet_ntoa(s.sin_addr),ntohs(s.sin_port));
s.sin_family=AF_INET;
s.sin_port=htons(atoi(argv[1]));
//s.sin_addr.s_addr=htonl(INADDR_ANY);
s.sin_addr.s_addr=inet_addr("192.168.0.104");
//printf("after inet : ip %ld port no %d\n",(long)inet_ntoa(s.sin_addr),ntohs(s.sin_port));
s1=bind(sfd,(struct sockaddr*)&s,sizeof(s));
client.sin_family=AF_INET;
client.sin_port=0;
client.sin_addr.s_addr=htonl(INADDR_ANY);
memset(client.sin_zero,'\0',sizeof(client.sin_zero));
bind(sfd,(struct sockaddr *)&client,sizeof(client));
int temp=sizeof(s);
while(1)
{
	printf("client : ");
	scanf("%s",buf);
	if(!strcmp(buf,"exit"))
	{
	printf("ENDING \n\nBYE");
	exit(-1);
	}
	//int temp=sizeof(client);
	//len=recvfrom(sfd,&buf,1000,0,(struct sockaddr *)&client,&temp);
	sendto(sfd,&buf,1000,0,(struct sockaddr *)&s,temp);
	len=recvfrom(sfd,&buf,1000,0,(struct sockaddr  *)&s,&temp);
	buf[len]='\0';
	printf("server = %s\n",buf);
	//scanf("%s",buf);
}
return 1;
}
