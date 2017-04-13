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
int sfd=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in s,server,client;int len,n,i,news,s1;
char buf[100];
//strcpy(buf,argv[2]);
//itoa(inet_ntoa(s.sin_addr),buf);
printf("before binding : ip %ld port no %d\n",(long)inet_ntoa(s.sin_addr),ntohs(s.sin_port));
s.sin_family=AF_INET;
s.sin_port=htons(atoi(argv[1]));
s.sin_addr.s_addr=htonl(INADDR_ANY);
s.sin_addr.s_addr=inet_addr("192.168.0.104");
printf("after inet : ip %ld port no %d\n",(long)inet_ntoa(s.sin_addr),ntohs(s.sin_port));
s1=bind(sfd,(struct sockaddr*)&s,sizeof(s));
printf("after bind : ip %ld port no %d\n",(long)inet_ntoa(s.sin_addr),ntohs(s.sin_port));
s1=listen(sfd,5);
printf("server waiting for clients \n");
news=accept(sfd,(struct sockaddr*)&client,&len);
//printf("connected to client ");
n=recv(news,&buf,100,0);
buf[n]='\0';
FILE *fp=fopen(buf,"r");
char filename[100];
strcpy(filename,buf);
if(fp<0)
{
	printf("error finding the file ");
	exit(-1);		
}
n=recv(news,&buf,100,0);
buf[n]='\0';
int public_key=atoi(buf);
pid_t pid=fork();
if(pid==0)
{
execlp("/usr/bin/python","python","rsaenc.py",filename,buf,NULL);
}
else
{
wait(NULL);
char c;
int co=0;
//printf("hi 2");
FILE *gp=fopen("output.txt","r");
while((c=fgetc(gp))!=EOF)
{
	buf[co++]=c;
}
buf[co]='\0';
//printf(" hi %s",buf);
n=strlen(buf);
send(news,&buf,co,0);
close(sfd);
close(news);
return 0;
}
}
