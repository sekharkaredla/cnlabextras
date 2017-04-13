#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
int main(int argc,char *argv[])
{
int sfd=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in s;
char buf[20];
//itoa(inet_ntoa(s.sin_addr),buf);
printf("before binding : ip %ld port no %d\n",(long)inet_ntoa(s.sin_addr),ntohs(s.sin_port));
s.sin_family=AF_INET;
s.sin_port=htons(atoi(argv[1]));
s.sin_addr.s_addr=htonl(INADDR_ANY);
s.sin_addr.s_addr=inet_addr("172.16.5.254");
printf("after inet : ip %ld port no %d\n",(long)inet_ntoa(s.sin_addr),ntohs(s.sin_port));
int s1;
s1=bind(sfd,(struct sockaddr*)&s,sizeof(s));
printf("after bind : ip %ld port no %d\n",(long)inet_ntoa(s.sin_addr),ntohs(s.sin_port));
return 0;
}
