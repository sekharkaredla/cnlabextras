#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(int argc, char *argv[])
{
	int sfd,lfd,len,choice,s,n;
	char str[100],str1[100],err[100];
	struct sockaddr_in saddr,caddr;
		sfd=socket(AF_INET,SOCK_STREAM,0); //create an unnamed TCP socket
	if(sfd<0)
	{
		perror("FdError");
		exit(-1);
	}
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family=AF_INET;
	//initialize the server address buffer
	saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	saddr.sin_port=htons(atoi(argv[1]));
	s=connect(sfd,(struct sockaddr*)&saddr,sizeof(saddr));//connect to the sender
	if(s<0)
	{
		perror("connect error");
		exit(-1);
	}
	for(;;)
	{
		n=recv(sfd,&str,100,0);
		//read the frames from the sender
		if(!strncmp(str,"exit",4))
		{
			printf("Exiting.............\n");
			break;
		}
		str[n]='\0';
		printf("\nReceived message is: %s\n Are there any errors?(1-Yes 0-No): ",str);
		scanf("%d",&choice);
		if(!choice)
			write(sfd,"-1",sizeof("-1"));
		else
		{
			printf("Enter the sequence no of the frame where error has occured: ");
			scanf("%s",&err);
			write(sfd,&err,sizeof(err));
			n=read(sfd,&str,20);
			str[n]='\0';
			printf("\n\nReceived the re-transmitted frames: %s\n\n",str);
		}
	}
}
